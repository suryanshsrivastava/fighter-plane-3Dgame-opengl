#include "sea.h"
#include "main.h"

Sea::Sea(float x, float y, float z, float width, float length, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->width = width;
    this->length = length;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        width, 0.0f, length,
       -width, 0.0f, -length,
        width, 0.0f, -length,

       -width, 0.0f, length,
        width, 0.0f, length,
       -width, 0.0f, -length, 
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Sea::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

// void Sea::set_position(float x, float y) {
//     this->position = glm::vec3(x, y, 0);
// }

Shining::Shining(float x, float z) {
    this->position = glm::vec3(x, 0, z);
    // this->rotation = 0;
    this->radius=1;

    GLfloat vertex_buffer_data[900]; 
    int sides = 100;
    float angle = (2*M_PIl)/sides;

    for(int i =0; i < sides;i++)
    {
        vertex_buffer_data[9*i] = 0.0f;
        vertex_buffer_data[9*i + 1] = 0.0f;  
        vertex_buffer_data[9*i + 2] = 0.0f;

        vertex_buffer_data[9*i + 3] = radius*cos(i*angle); 
        vertex_buffer_data[9*i + 4] = 0.0f;
        vertex_buffer_data[9*i + 5] = radius*sin(i*angle);

        vertex_buffer_data[9*i + 6] = radius*cos((i+1)*angle); 
        vertex_buffer_data[9*i + 7] = 0.0f;
        vertex_buffer_data[9*i + 8] = radius*sin((i+1)*angle);
    }

    this->object = create3DObject(GL_TRIANGLES, 3*sides, vertex_buffer_data, COLOR_YELLOW, GL_FILL);
}

void Shining::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Shining::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

CheckpointIsland::CheckpointIsland(float x, float z, float rotation) {
    this->position = glm::vec3(x, 0, z);
    this->rotation = rotation;
    this->radius=1;
    this->current=true;

    GLfloat vertex_buffer_data_island[] = {
        -50.0f, 0.01f, 50.0f,
        -50.0f, 0.01f, -50.0f,
        50.0f, 0.01f, 50.0f,

        50.0f, 0.01f, -50.0f,
        -50.0f, 0.01f, -50.0f,
        50.0f, 0.01f, 50.0f,

        0.0f, 0.01f, -75.0f,
        -50.0f+(float)(rand()%50), 0.0f, 50.0f,
        (float)(rand()%50), 0.0f, 50.0f,

        0.0f, 0.01f, -75.0f,
        -50.0f+(float)(rand()%50), 0.0f, -50.0f,
        (float)(rand()%50), 0.0f, -50.0f,

        -75.0f, 0.01f, 0.0f, 
        -50.0f, 0.01f, -50.0f+(float)(rand()%50),
        -50.0f, 0.01f, (float)(rand()%50),

        75.0f, 0.01f, 0.0f, 
        50.0f, 0.01f, -50.0f+(float)(rand()%50),
        50.0f, 0.01f, (float)(rand()%50),

        // 0.0f, 50.0f, 0.0f,
        // 50.0f, 0.0f, -50.0f+(float)(rand()%50),
        // 50.0f, 0.0f, (float)(rand()%50),
    };
    this->island = create3DObject(GL_TRIANGLES, 3*6, vertex_buffer_data_island, COLOR_GROUND , GL_FILL);
}

void CheckpointIsland::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate*rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->island);
}

void CheckpointIsland::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

CheckpointArrow::CheckpointArrow(float x, float y, float z){
    this->position = glm::vec3(x, y, z);
    this->height=30.0f;
    this->arrowhead = 10.0f;
    this->width = 5.0f;
    this->arrowwidth = 10.0f;
    this->equilibrium_y = y;

    this->rotatespeed = 65.0f;
    this->indicatespeed = 0.25f;
    this->moveup = true;

    GLfloat vertex_buffer_data_needle[] = {
        -width*0.5f,    0, 0,
         width*0.5f,    0, 0,
        -width*0.5f, -height+arrowhead, 0,

         width*0.5f,    0, 0,
        -width*0.5f, -height+arrowhead, 0,
         width*0.5f, -height+arrowhead, 0,

            0, -height, 0,
      -arrowwidth*0.5f, -height+arrowhead, 0,
       arrowwidth*0.5f, -height+arrowhead, 0,    
    }; 

    this->arrow = create3DObject(GL_TRIANGLES, 9, vertex_buffer_data_needle, COLOR_RED, GL_FILL);
}

void CheckpointArrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotatespeed * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate*rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->arrow);
}

void CheckpointArrow::movement() {
    rotatespeed+=5.0f;
    if(moveup){
        this->position.y += this->indicatespeed;
        if(this->position.y >= equilibrium_y+10.0f)
            moveup=false;
    }
    else
    {
        this->position.y -= this->indicatespeed;
        if(this->position.y < equilibrium_y-10.0f)
            moveup=true;
    }
}