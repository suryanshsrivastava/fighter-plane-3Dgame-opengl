#include "main.h"
#include "timer.h"
#include "plane.h"
#include "sea.h"
#include "dashboard.h"
#include "objects.h"
#include "combat.h"

using namespace std;

GLMatrices Matrices;
GLMatrices MatricesDashboard;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Plane plane;

Sea c;
vector<Shining> shines;

vector<Ring> rings;
vector<Volcano> volcanoes;

int checkpoint =0;
vector<CheckpointIsland> islands;
vector<CheckpointArrow> checks;
vector<Ring> checkrings;

vector<Missile> missiles;
int ammo = 1000;
int n = 1000;

vector<Parachute> parachutes;
vector<Cannons> cannons;
vector<Cannon_Missile> cannonbullets;
int cannonammo = 0;

SpeedDial speeddash;
Speed speed;
// Digit altitude;
SpeedDial altitudemeter;
Speed altitude;

Fuel fuellevel0;
Fuel fuellevel1;
Fuel fuellevel2;
Fuel fuellevel3;
Fuel fuellevel4;
Fuel fuellevel5;
vector <Fueltank> fuelup;
float theta = 0;
float fi = 0;

float planecenter[3];
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);
int cam = 4;
// bool gravity_effect = true;
// bool locked = false;
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
    glm::vec3 Dashcameye ( 0, 0, -1);
    glm::vec3 Dashtarget ( 0, 0, 0);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( current.eye_x, current.eye_y, current.eye_z);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target ( current.target_x, current.target_y, current.target_z);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up ( current.up_x, current.up_y, current.up_z);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    MatricesDashboard.view = glm::lookAt( Dashcameye, Dashtarget, up );
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 DashboardVP = MatricesDashboard.projection * MatricesDashboard.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    c.draw(VP);
    for(int i=0; i<shines.size(); i++) {
        shines[i].draw(VP);
    }

    plane.draw(VP);
    
    for(int i=0; i<rings.size(); i++) {
        rings[i].draw(VP);
    }
    for(int i=0; i<volcanoes.size(); i++) {
        volcanoes[i].draw(VP);
    }

    islands[checkpoint].current = true;
    for(int i=0; i<islands.size(); i++) {
        islands[i].draw(VP);
    }
    for(int i=0; i<checks.size(); i++) {
        if (islands[i].current) {
            checks[i].draw(VP);
        }
    }
    for(int i=0; i<checkrings.size(); i++) {
        checkrings[i].draw(VP);
    }
    for(int i=0; i<cannons.size(); i++) {
        cannons[i].draw(VP);
    }
    for(int i=0; i<cannonbullets.size(); i++) {
            // printf("made\n");

        cannonbullets[i].draw(VP);
    }
    for(int i=0; i<parachutes.size(); i++) {
        parachutes[i].draw(VP);
    }


    for(int i=0; i<n; i++) {
        if (missiles[i].fired) {
            missiles[i].draw(VP);
        }
    }

    speeddash.draw(DashboardVP);
    speed.draw(DashboardVP);
    // altitude.draw(DashboardVP);
    if (plane.fuelleft>=9) {
        fuellevel1.draw(DashboardVP);
        fuellevel2.draw(DashboardVP);
        fuellevel3.draw(DashboardVP);
        fuellevel4.draw(DashboardVP);
        fuellevel5.draw(DashboardVP);
    }
    else if (plane.fuelleft>=7) {
        fuellevel1.draw(DashboardVP);
        fuellevel2.draw(DashboardVP);
        fuellevel3.draw(DashboardVP);
        fuellevel4.draw(DashboardVP);
    }
    else if (plane.fuelleft>=5) {
        fuellevel1.draw(DashboardVP);
        fuellevel2.draw(DashboardVP);
        fuellevel3.draw(DashboardVP);
    }
    else if (plane.fuelleft>=3) {
        fuellevel1.draw(DashboardVP);
        fuellevel2.draw(DashboardVP);
    }
    else if (plane.fuelleft>=1) {
        fuellevel1.draw(DashboardVP);
    }
    else
    {
        fuellevel0.draw(DashboardVP);
    }
}

void camera_view_change () {
    float R = plane.length + 5.0f;
    
    //Plane View
    if(cam == 1)
    {
        current.eye_x=plane.position.x + (plane.length + plane.nose)*(sin(plane.yaw* M_PI / 180.0f)*cos(plane.pitch* M_PI / 180.0f)); 
        current.eye_y=plane.position.y + (plane.length + plane.nose)*sin(-plane.pitch* M_PI / 180.0f); 
        current.eye_z=plane.position.z + (plane.length + plane.nose)*(cos(plane.yaw* M_PI / 180.0f)*cos(plane.pitch* M_PI / 180.0f));
        
        current.target_x=plane.position.x + (plane.length + plane.nose + 1)*(sin(plane.yaw* M_PI / 180.0f)*cos(plane.pitch* M_PI / 180.0f)); 
        current.target_y=plane.position.y + (plane.length + plane.nose + 1)*sin(-plane.pitch* M_PI / 180.0f); 
        current.target_z=plane.position.z + (plane.length + plane.nose + 1)*(cos(plane.yaw* M_PI / 180.0f)*cos(plane.pitch* M_PI / 180.0f));
        
        current.up_x=0; current.up_y=1; current.up_z=0;
    }
    // Top View
    else if(cam == 2)
    {
        current.eye_x=plane.position.x; current.eye_y=plane.position.y + 20.0f; current.eye_z=plane.position.z;
        
        current.target_x=plane.position.x; current.target_y=plane.position.y; current.target_z=plane.position.z;
        
        current.up_x=0; current.up_y=0; current.up_z=1;
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
        current.eye_x=plane.position.x - R*(sin(plane.yaw* M_PI / 180.0f)); current.eye_y=plane.position.y + 4.0f; current.eye_z=plane.position.z - R*(cos(plane.yaw* M_PI / 180.0f)); 
        
        current.target_x=plane.position.x + R*(sin(plane.yaw* M_PI / 180.0f)); current.target_y=plane.position.y; current.target_z=plane.position.z + R*(cos(plane.yaw* M_PI / 180.0f));
        
        current.up_x=0; current.up_y=1; current.up_z=0;
    }

    else if (cam == 5) {
        current.eye_x=plane.position.x - R*(sin(theta)*cos(fi)); current.eye_y=plane.position.y - R*cos(fi); current.eye_z=plane.position.z - R*(sin(theta)*sin(fi)); 
        
        current.target_x=plane.position.x + R*(sin(plane.yaw* M_PI / 180.0f)); current.target_y=plane.position.y; current.target_z=plane.position.z + R*(cos(plane.yaw* M_PI / 180.0f));
        
        current.up_x=0; current.up_y=1; current.up_z=0;
    } 
}

void tick_elements() {
    plane.tick();
    for(int i=0; i<missiles.size(); i++) {
        if (missiles[i].position.y<=-10.0f) {
            // printf("%f", missiles[i].position.y);
            missiles.erase(missiles.begin()+i);
        }
        else
        {
            // printf("movinggggg%f", missiles[i].position.y);
            missiles[i].tick(plane.yaw);
        }        
    }
    for(int i = 0; i < parachutes.size(); i++) 
    {
        parachutes[i].movement();
    }
    for(int i = 0; i < cannons.size(); i++)
    {
        if ((int)sqrt(pow(planecenter[0]-cannons[i].position.x, 2)+pow(planecenter[2]-cannons[i].position.z, 2))<= 50) {
            if (cannonammo == 100) {
            glm::vec3 a = plane.position;
            glm::vec3 b = cannons[i].position;
            glm::vec3 c = a-b;
            glm::vec3 d = glm::normalize(c); //self assignmnet works?
            printf("made  %f %f %f\n", d.x, d.y, d.z);
            cannonbullets.push_back(Cannon_Missile(cannons[i].position.x, cannons[i].position.y, cannons[i].position.z, d*(1.0f)));
        }
        }
    }
    cannonammo++;
    if (cannonammo == 200) {
            cannonammo = 0;
    }
    
    for(int i = 0; i < cannonbullets.size(); i++) {
        printf("%f %f %f\n", cannonbullets[i].position.x, cannonbullets[i].position.y, cannonbullets[i].position.z);
        cannonbullets[i].movement();
    }

    for(int i=0; i<checks.size(); i++) checks[i].movement();
    // plane.gravity(gravity_effect);
    camera_view_change();
    planecenter[0] = plane.position.x + (plane.length + plane.nose + plane.engine)*0.5*(sin(plane.yaw* M_PI / 180.0f)*cos(plane.pitch* M_PI / 180.0f));
    planecenter[1] = plane.position.y + (plane.length + plane.nose + plane.engine)*0.5*(sin(-plane.pitch* M_PI / 180.0f));
    planecenter[2] = plane.position.z + (plane.length + plane.nose + plane.engine)*0.5*(cos(plane.yaw* M_PI / 180.0f)*cos(plane.pitch* M_PI / 180.0f));
    // speed.tick_speed(plane.speed);
    
    //No Fly Zone: Checking proximity with Volcanoes
    for(int i=0; i<volcanoes.size(); i++) {
        if (plane.detect_collision(planecenter ,volcanoes[i].position.x, volcanoes[i].position.y, volcanoes[i].position.z, volcanoes[i].radius+25.0f)) {
            printf("too close\n");
            quit(window);  
        }
    }

    //Rings
    for(int i=0; i<rings.size(); i++) {
        if (detect_collision(plane.position, rings[i].position, plane.length , rings[i].innerradius)) {
            rings[i].collected = true;
        }
    }
    for(int i=0; i<checkrings.size(); i++) {
        if (detect_collision(plane.position, checkrings[i].position, plane.length , checkrings[i].innerradius)) {
            checkrings[i].collected = true;
        }
    }

    //missiles
    for(int i=0; i < cannons.size(); i++) 
    {
        for(int j = 0; j < missiles.size(); j++)
        {
            if (detect_collision(missiles[j].position, cannons[i].position, cannons[i].spread , missiles[j].length)) {
            cannons[i].destroyed = true;
            if (islands[i].current) {
                checkpoint++;
                cannons.erase(cannons.begin()+i);
            }
            else
            {
                cannons[i].destroyed = false;
            }
            }
        }
    }
    for(int i=0; i < parachutes.size(); i++) 
    {
        for(int j=0; j < missiles.size(); j++)
        {
            if (detect_collision(missiles[j].position, parachutes[i].position, parachutes[i].outerradius , missiles[j].length)) {
            parachutes[i].destroyed = true;
            }
        }
    }
    for(int i=0; i < parachutes.size(); i++){
        if (parachutes[i].destroyed) {
            parachutes.erase(parachutes.begin()+i);
        }
    } 
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
    if (num4) {
        cam = 5;
    }
    
    
    // rise
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    if(space){
        // gravity_effect = false;
        plane.move_rise(true);
    }
    int s = glfwGetKey(window, GLFW_KEY_S);
    if(s) {
        plane.move_rise(false);
    }
    
    //pitch
    int r = glfwGetKey(window, GLFW_KEY_R);
    if (r) {
        plane.tick_pitch(true);
    }
    int f = glfwGetKey(window, GLFW_KEY_F);
    if (f) {
        plane.tick_pitch(false);
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
        speed.tick_speed(plane.speed);

    }
    else
    {
        speed.speedrotate = -90;
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

    int fire = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (fire) {
        printf("ammo:%i fired?:%i\n", ammo, missiles[ammo-1].fired);
        missiles[ammo-1].set_position(planecenter[0], planecenter[1], planecenter[2], plane.yaw);
        missiles[ammo-1].fired=true;
        printf("ammo:%i fired?:%i\n", ammo, missiles[ammo-1].fired);
        ammo--;
    }
    // double xy = glfwGetCursorPos(window, &x, &y);
    // if 
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    plane       = Plane(0,50.0f, 0, COLOR_METAL);
    
    c           = Sea(0, 0, 0, 1000.0f, 1000.0f, COLOR_SEABLUE);
    for(int i=0; i<2000; i++) {
        shines.push_back(Shining(-c.width + rand()%(int)(2*c.width), -c.length + rand()%(int)(2*c.length)));
    }

    for(int i=0; i<10; i++) {
        rings.push_back(Ring(-c.width + rand()%(int)(2*c.width), 20.0f,-c.length + rand()%(int)(2*c.length)));
    }
    for(int i=0; i<20; i++) {
        volcanoes.push_back(Volcano(-c.width + rand()%(int)(2*c.width), -c.length + rand()%(int)(2*c.length), rand()%360));
    }
    
    //Obstacle Course
    for(int i=0; i<10; i++) {
        islands.push_back(CheckpointIsland(-c.width + rand()%(int)(2*c.width), -c.length + rand()%(int)(2*c.length), (float)(rand()%360)));
    }
    for(int i=0; i<10; i++) {
        checks.push_back(CheckpointArrow(islands[i].position.x, 80.0f, islands[i].position.z));
    }
    for(int i=0; i<10; i++) {
        checkrings.push_back(Ring(islands[i].position.x, 50.0f,islands[i].position.z));
    }
    for(int i=0; i<10; i++) {
        cannons.push_back(Cannons(islands[i].position.x, 5.0f, islands[i].position.z));
    }
    for(int i=0; i<70; i++) {
        parachutes.push_back(Parachute(-c.width + rand()%(int)(2*c.width), rand()%100,-c.length + rand()%(int)(2*c.length)));
    }
    parachutes.push_back(Parachute(0, 20,10));
    for(int i=0; i<ammo; i++) {
        missiles.push_back(Missile(planecenter[0], planecenter[1], planecenter[2]));
    }

    //Dashboard Variables
    speeddash   = SpeedDial(-3.0f, -4.0f);
    speed       = Speed(-3.0f, -4.0f);
    // altitudemeter = SpeedDial(-3.0)

    // altitude    = Digit('0', 0.0f, 0.0f);
    fuellevel0  = Fuel(3.0f, -4.0f, FUEL_RED);
    fuellevel1  = Fuel(3.0f, -4.0f, FUEL_ORANGE);
    fuellevel2  = Fuel(3.0f, -3.4f, FUEL_YELLOW);
    fuellevel3  = Fuel(3.0f, -2.8f, FUEL_YELLOW);
    fuellevel4  = Fuel(3.0f, -2.2f, FUEL_GREEN);
    fuellevel5  = Fuel(3.0f, -1.6f, FUEL_GREEN);
    for(int i=0; i<30; i++) {
        fuelup.push_back(Fueltank(-c.width + rand()%(int)(2*c.width), 80.0f, -c.length + rand()%(int)(2*c.length)));
    }
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
            printf("checkpoint: %f, %f\n", islands[checkpoint].position.x, islands[checkpoint].position.z );
            tick_elements();
            // printf("%f\n", planecenter[0]);
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(glm::vec3 a, glm::vec3 b, float r1, float r2) {
    return ((int)sqrt(pow(a.x-b.x, 2)+pow(a.y-b.y, 2)+pow(a.z-b.z,2)) <= (r1 + r2));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective((float)glm::radians(60.0f), 1.0f, 3.0f, 1000.0f);
    MatricesDashboard.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
