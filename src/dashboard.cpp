#include "dashboard.h"
#include "main.h"

Dashboard::Dashboard(float x, float y, float z, float speed, float fuel, float altitude) {
    this->position = glm::vec3(x, y, z);
    this->speed_indicator_rotation = 0;

    GLfloat vertex_buffer_data_head[900]; 
    int sides = 100;
    float radius = 1.5f;
    float angle = (2*M_PIl)/sides;

    for(int i =0; i < sides/2;i++)
    {
        vertex_buffer_data_head[9*i] = 0.0f;
        vertex_buffer_data_head[9*i + 1] = 0.0f;  
        vertex_buffer_data_head[9*i + 2] = 0.0f;

        vertex_buffer_data_head[9*i + 3] = radius*cos(i*angle); 
        vertex_buffer_data_head[9*i + 4] = radius*sin(i*angle) ;
        vertex_buffer_data_head[9*i + 5] = 0.0f;

        vertex_buffer_data_head[9*i + 6] = radius*cos((i+1)*angle); 
        vertex_buffer_data_head[9*i + 7] = radius*sin((i+1)*angle); 
        vertex_buffer_data_head[9*i + 8] = 0.0f;
    }

    glPointSize(10);
    this->object = create3DObject(GL_TRIANGLES, 1.5f*sides, vertex_buffer_data_head, COLOR_GREEN, GL_POINT);
}

void Dashboard::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->speed_indicator_rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Dashboard::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
