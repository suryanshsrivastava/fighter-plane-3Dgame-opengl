#include "main.h"
#include "timer.h"
#include "plane.h"
#include "sea.h"
#include "dashboard.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Plane plane;
Sea c; 
Dashboard dash;
// Plane ball2;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);
int cam = 4;
bool gravity_effect = true;
bool locked = false;
// struct camera_view planeview;
// struct camera_view topview;
// struct camera_view towerview;
// struct camera_view followcam;
struct camera_view current;

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( current.eye_x, current.eye_y, current.eye_z);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target ( current.target_x, current.target_y, current.target_z);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up ( current.up_x, current.up_y, current.up_z);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    c.draw(VP);
    plane.draw(VP);
    dash.draw(VP);
}

void camera_view_change () {
    //Plane View
    if(cam == 1)
    {
        current.eye_x=plane.position.x; current.eye_y=plane.position.y; current.eye_z=plane.position.z + plane.length + plane.nose;
        
        current.target_x=plane.position.x; current.target_y=plane.position.y; current.target_z=plane.position.z + plane.length + plane.nose + 1;
        
        current.up_x=0; current.up_y=1; current.up_z=0;
    }
    // Top View
    else if(cam == 2)
    {
        current.eye_x=plane.position.x; current.eye_y=plane.position.y + 10.0f; current.eye_z=plane.position.z-0.00001f; //why this doesn't work without that difference?
        
        current.target_x=plane.position.x; current.target_y=plane.position.y; current.target_z=plane.position.z;
        
        current.up_x=0; current.up_y=1; current.up_z=0;
    }
    // Tower View
    else if(cam == 3)
    {
        current.eye_x=-4; current.eye_y=plane.position.y+4.0f; current.eye_z=-4; //why is this inverted ffs?
        
        current.target_x=plane.position.x; current.target_y=plane.position.y; current.target_z=plane.position.z;
        
        current.up_x=0; current.up_y=1; current.up_z=0;
    }
    // Follow Cam
    else if(cam == 4)
    {
        current.eye_x=plane.position.x; current.eye_y=plane.position.y + 4.0f; current.eye_z=plane.position.z - plane.length - 5.0f; 
        
        current.target_x=plane.position.x; current.target_y=plane.position.y; current.target_z=plane.position.z + plane.length + 5.0f;
        
        current.up_x=0; current.up_y=1; current.up_z=0;
    }
}

void tick_elements() {
    plane.tick();
    plane.gravity(gravity_effect);
    camera_view_change();
}

void tick_input(GLFWwindow *window) {
    
    //First Person view
    int num8 = glfwGetKey(window, GLFW_KEY_KP_8);
    if (num8) {
        cam = 1;
    }
    //Top view
    int num5 = glfwGetKey(window, GLFW_KEY_KP_5);
    if (num5) {
        cam = 2;
    }
    //Tower view
    int num6 = glfwGetKey(window, GLFW_KEY_KP_6);
    if(num6) {
        cam = 3;
    }
    //Follow Cam view
    int num2 = glfwGetKey(window, GLFW_KEY_KP_2);
    if(num2) {
        cam = 4;
    }
    int num4 = glfwGetKey(window, GLFW_KEY_KP_4);
    
    // rise / pitch?
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    if(space){
        gravity_effect = false;
        plane.move_rise();
    }
    else 
    {
        if(!locked){
            gravity_effect = true;
        }
    }
    int lock = glfwGetKey(window, GLFW_KEY_LEFT_ALT);
    if (lock) {
        locked = !locked;
        gravity_effect = !gravity_effect;
    }
    
    //yaw
    int cc = glfwGetKey(window, GLFW_KEY_Q);
    if (cc) {
        plane.tick_yaw(false);
    }
    int c = glfwGetKey(window, GLFW_KEY_E);
    if (c) {
        plane.tick_yaw(true);
    }
    
    //forward 
    int w = glfwGetKey(window, GLFW_KEY_W);
    if (w) {
        plane.tick_forward();
    }
    

    //roll/tilt
    int left = glfwGetKey(window, GLFW_KEY_A);
    if (left) {
        plane.tick_roll(false);
    }
    
    int right = glfwGetKey(window, GLFW_KEY_D);
    if (right) {
        plane.tick_roll(true);
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    plane       = Plane(0, 10.0f, 0, COLOR_METAL);
    c           = Sea(0, 0, 0, 1000.0f, 1000.0f, COLOR_BLUE);
    dash        = Dashboard(current.eye_x, current.eye_y, current.eye_y, plane.speed, plane.fuelleft, plane.position.y);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 800;
    int height = 800;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            printf("eye:%f  target:%f forward:%f altitude:%f\n", current.eye_y, current.target_y, plane.position.z, plane.position.y);
            tick_elements();
            // printf("eye:%f  target:%f position_y:%f\n", current.eye_y, current.target_y, plane.position.y);
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective((float)glm::radians(60.0f), 1.0f, 3.0f, 1000.0f);
}
