#include "dashboard.h"
#include "main.h"

SpeedDial::SpeedDial(float x, float y){
    this->position = glm::vec3(x, y, 0);

    GLfloat vertex_buffer_data[900]; 
    int sides = 100;
    float radius = 1.0f;
    float angle = (2*M_PIl)/sides;

    for(int i =0; i < sides/2;i++)
    {
        vertex_buffer_data[9*i] = 0.0f;
        vertex_buffer_data[9*i + 1] = 0.0f;  
        vertex_buffer_data[9*i + 2] = 0.0f;

        vertex_buffer_data[9*i + 3] = radius*cos(i*angle); 
        vertex_buffer_data[9*i + 4] = radius*sin(i*angle) ;
        vertex_buffer_data[9*i + 5] = 0.0f;

        vertex_buffer_data[9*i + 6] = radius*cos((i+1)*angle); 
        vertex_buffer_data[9*i + 7] = radius*sin((i+1)*angle); 
        vertex_buffer_data[9*i + 8] = 0.0f;
    }

    glPointSize(10);
    this->object = create3DObject(GL_TRIANGLES, 1.5f*sides, vertex_buffer_data, COLOR_GREEN, GL_POINT);
}

void SpeedDial::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

Speed::Speed(float x, float y){
    this->position = glm::vec3(x, y, 0);
    this->speedrotate = -90;
    GLfloat vertex_buffer_data_needle[] = {
        -0.025f,    0, 0,
         0.025f,    0, 0,
        -0.025f, 0.75f, 0,

         0.025f,    0, 0,
        -0.025f, 0.75f, 0,
         0.025f, 0.75f, 0,

            0, 1.0f, 0,
      -0.125f, 0.75f, 0,
       0.125f, 0.75f, 0,    
    }; 
    
    glPointSize(10);
    this->object = create3DObject(GL_TRIANGLES, 9, vertex_buffer_data_needle, COLOR_BLACK, GL_FILL);
}

void Speed::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
     glm::mat4 rotate = glm::rotate((float) (this->speedrotate * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate*rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Speed::tick_speed(float speed) {
    speedrotate += speed;
}

Fuel::Fuel(float x, float y, color_t COLOR){
    this->position = glm::vec3(x, y, 0);
    this->height = 0.5f;
    this->width = 1.0f;
    GLfloat vertex_buffer_data_meter[] = {
        0, 0, 0,
        width, 0, 0,
        0, height, 0,

        0, height, 0,
        width, 0, 0,
        width, height, 0,   
    }; 
    
    glPointSize(10);
    this->object = create3DObject(GL_TRIANGLES, 9, vertex_buffer_data_meter, COLOR, GL_FILL);
}

void Fuel::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //  glm::mat4 rotate = glm::rotate((float) (this->speedrotate * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}