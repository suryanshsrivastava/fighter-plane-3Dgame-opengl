#include "objects.h"
#include "main.h"
#include "plane.h"
#include "combat.h"

Missile::Missile(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;

    this->radius = 0.25f;
    this->length = 5.0f;
    this->front = 1.0f;
    this->back = 0.25f;

    this->fired=false;

    this->speed_z = 1.25f;
    this->speed_y = 0.0f;

    int sides = 100;
    float angle = (2*M_PI)/sides;

    //Pointy end - The Dictator
    GLfloat vertex_buffer_data_front[1800]; 
    
    for(int i = 0; i < sides; i++)
    {
        vertex_buffer_data_front[9*i] = 0.5f*radius*cos(i*angle);
        vertex_buffer_data_front[9*i + 1] = 0.5f*radius*sin(i*angle);  
        vertex_buffer_data_front[9*i + 2] = front + length + back;

        vertex_buffer_data_front[9*i + 3] = radius*cos(i*angle); 
        vertex_buffer_data_front[9*i + 4] = radius*sin(i*angle);
        vertex_buffer_data_front[9*i + 5] = length + back;

        vertex_buffer_data_front[9*i + 6] = radius*cos((i+1)*angle); 
        vertex_buffer_data_front[9*i + 7] = radius*sin((i+1)*angle); 
        vertex_buffer_data_front[9*i + 8] = length + back;
    }
    for(int i = 100; i < sides+100; i++)
    {
        vertex_buffer_data_front[9*i] = radius*cos((i+1)*angle);
        vertex_buffer_data_front[9*i + 1] = radius*sin((i+1)*angle);  
        vertex_buffer_data_front[9*i + 2] = length + back;

        vertex_buffer_data_front[9*i + 3] = 0.5f*radius*cos(i*angle); 
        vertex_buffer_data_front[9*i + 4] = 0.5f*radius*sin(i*angle);
        vertex_buffer_data_front[9*i + 5] = front + length + back;    

        vertex_buffer_data_front[9*i + 6] = 0.5f*radius*cos((i+1)*angle); 
        vertex_buffer_data_front[9*i + 7] = 0.5f*radius*sin((i+1)*angle); 
        vertex_buffer_data_front[9*i + 8] = front + length + back;
    }
    this->pointyend = create3DObject(GL_TRIANGLES, 2*sides*3, vertex_buffer_data_front, COLOR_BLACK, GL_FILL);

    //Cyllinderical Body
    GLfloat vertex_buffer_data_body[2700]; 

    for(int i =0; i < sides; i++)
    {
        vertex_buffer_data_body[9*i] = radius*cos(i*angle);
        vertex_buffer_data_body[9*i + 1] = radius*sin(i*angle);  
        vertex_buffer_data_body[9*i + 2] = length + back;
        
        vertex_buffer_data_body[9*i + 3] = radius*cos(i*angle); 
        vertex_buffer_data_body[9*i + 4] = radius*sin(i*angle);
        vertex_buffer_data_body[9*i + 5] = back;

        vertex_buffer_data_body[9*i + 6] = radius*cos((i+1)*angle); 
        vertex_buffer_data_body[9*i + 7] = radius*sin((i+1)*angle); 
        vertex_buffer_data_body[9*i + 8] = back;
    }
    for(int i =100; i < sides+100; i++)
    {
        vertex_buffer_data_body[9*i] = radius*cos((i+1)*angle);
        vertex_buffer_data_body[9*i + 1] = radius*sin((i+1)*angle);  
        vertex_buffer_data_body[9*i + 2] = back;
        
        vertex_buffer_data_body[9*i + 3] = radius*cos(i*angle); 
        vertex_buffer_data_body[9*i + 4] = radius*sin(i*angle);
        vertex_buffer_data_body[9*i + 5] = length + back;

        vertex_buffer_data_body[9*i + 6] = radius*cos((i+1)*angle); 
        vertex_buffer_data_body[9*i + 7] = radius*sin((i+1)*angle); 
        vertex_buffer_data_body[9*i + 8] = length + back;
    }
    
    for(int i =200; i < sides+200; i++)
    {
        vertex_buffer_data_body[9*i] = 0.5*radius*cos((i+1)*angle);
        vertex_buffer_data_body[9*i + 1] = 0.5*radius*sin((i+1)*angle);  
        vertex_buffer_data_body[9*i + 2] = 0.0f;

        vertex_buffer_data_body[9*i + 3] = radius*cos(i*angle); 
        vertex_buffer_data_body[9*i + 4] = radius*sin(i*angle);
        vertex_buffer_data_body[9*i + 5] = back;

        vertex_buffer_data_body[9*i + 6] = radius*cos((i+1)*angle); 
        vertex_buffer_data_body[9*i + 7] = radius*sin((i+1)*angle); 
        vertex_buffer_data_body[9*i + 8] = back;
    }

    this->load = create3DObject(GL_TRIANGLES, 3*sides*3, vertex_buffer_data_body, COLOR_METAL, GL_FILL);

    GLfloat vertex_buffer_data_thrust[1800]; 

    for(int i =0; i < sides; i++)
    {
        vertex_buffer_data_thrust[9*i] = radius*cos(i*angle);
        vertex_buffer_data_thrust[9*i + 1] = radius*sin(i*angle);  
        vertex_buffer_data_thrust[9*i + 2] = back;

        vertex_buffer_data_thrust[9*i + 3] = 0.5f*radius*cos(i*angle); 
        vertex_buffer_data_thrust[9*i + 4] = 0.5f*radius*sin(i*angle);
        vertex_buffer_data_thrust[9*i + 5] = 0.0f;

        vertex_buffer_data_thrust[9*i + 6] = 0.5f*radius*cos((i+1)*angle); 
        vertex_buffer_data_thrust[9*i + 7] = 0.5f*radius*sin((i+1)*angle); 
        vertex_buffer_data_thrust[9*i + 8] = 0.0f;
    }
    for(int i =100; i < sides+100; i++)
    {
        vertex_buffer_data_thrust[9*i] = 0.0f;
        vertex_buffer_data_thrust[9*i + 1] = 0.0f;  
        vertex_buffer_data_thrust[9*i + 2] = 0.0f;

        vertex_buffer_data_thrust[9*i + 3] = 0.5*radius*cos(i*angle); 
        vertex_buffer_data_thrust[9*i + 4] = 0.5*radius*sin(i*angle);
        vertex_buffer_data_thrust[9*i + 5] = 0.0f;

        vertex_buffer_data_thrust[9*i + 6] = 0.5*radius*cos((i+1)*angle); 
        vertex_buffer_data_thrust[9*i + 7] = 0.5*radius*sin((i+1)*angle); 
        vertex_buffer_data_thrust[9*i + 8] = 0.0f;
    }
    this->thrust = create3DObject(GL_TRIANGLES, 2*sides*3, vertex_buffer_data_thrust, COLOR_ORANGE , GL_FILL);
}

void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // rotate          = glm::translate(glm::vec3(0, 0, 0)) * rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->pointyend);
    draw3DObject(this->load);
    draw3DObject(this->thrust);
}

void Missile::tick(float yaw) {
    if (this->fired) {
        // printf("moving\n");
        this->position.z += this->speed_z*(cos(yaw * M_PI / 180.0f));
        this->position.y += this->speed_y;
        this->position.x += this->speed_z*(sin(yaw * M_PI / 180.0f));
        this->speed_y -= 0.0163f;
    }
}

void Missile::set_position(float x, float y, float z, float yaw) {
    this->position = glm::vec3(x, y, z);
    this->rotation += yaw;
}

bounding_box_t Missile::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->length, this->radius*2 };
    return bbox;
}

Cannon_Missile::Cannon_Missile(float x, float y, float z, glm::vec3 d){
    this->position = glm::vec3(x, y, z);
    this->height=100.0f;
    this->innerradius=1;
    this->outerradius=2;
    this->width=10.0f;
    this->spread=3.0f;
    this->d = d;
    
    this->rotatespeed = 65.0f;
    
    this->pitch = 30;
    this->yaw = 0;

    int sides = 100;
    float angle = (2*M_PIl)/sides;

    GLfloat vertex_buffer_data_ring[5400]; 

    for(int i =0; i < sides; i++)
    {
        vertex_buffer_data_ring[9*i] = innerradius*cos(i*angle);
        vertex_buffer_data_ring[9*i + 1] = innerradius*sin(i*angle);  
        vertex_buffer_data_ring[9*i + 2] = width; 

        vertex_buffer_data_ring[9*i + 3] = innerradius*cos(i*angle); 
        vertex_buffer_data_ring[9*i + 4] = innerradius*sin(i*angle);
        vertex_buffer_data_ring[9*i + 5] = 0.0f;
        
        vertex_buffer_data_ring[9*i + 6] = innerradius*cos((i+1)*angle); 
        vertex_buffer_data_ring[9*i + 7] = innerradius*sin((i+1)*angle); 
        vertex_buffer_data_ring[9*i + 8] = 0.0f;
    }
    for(int i =100; i < sides+100; i++)
    {
        vertex_buffer_data_ring[9*i] = innerradius*cos((i+1)*angle);
        vertex_buffer_data_ring[9*i + 1] = innerradius*sin((i+1)*angle);  
        vertex_buffer_data_ring[9*i + 2] = 0.0f;

        vertex_buffer_data_ring[9*i + 3] = innerradius*cos(i*angle); 
        vertex_buffer_data_ring[9*i + 4] = innerradius*sin(i*angle);
        vertex_buffer_data_ring[9*i + 5] = width;

        vertex_buffer_data_ring[9*i + 6] = innerradius*cos((i+1)*angle); 
        vertex_buffer_data_ring[9*i + 7] = innerradius*sin((i+1)*angle); 
        vertex_buffer_data_ring[9*i + 8] = width;
    }
    for(int i =200; i < sides+200; i++)
    {
        vertex_buffer_data_ring[9*i] = outerradius*cos((i+1)*angle);
        vertex_buffer_data_ring[9*i + 1] = outerradius*sin((i+1)*angle);  
        vertex_buffer_data_ring[9*i + 2] = width;

        vertex_buffer_data_ring[9*i + 3] = innerradius*cos(i*angle); 
        vertex_buffer_data_ring[9*i + 4] = innerradius*sin(i*angle);
        vertex_buffer_data_ring[9*i + 5] = width;

        vertex_buffer_data_ring[9*i + 6] = innerradius*cos((i+1)*angle); 
        vertex_buffer_data_ring[9*i + 7] = innerradius*sin((i+1)*angle); 
        vertex_buffer_data_ring[9*i + 8] = width;
    }
    for(int i =300; i < sides+300; i++)
    {
        vertex_buffer_data_ring[9*i] = outerradius*cos(i*angle);
        vertex_buffer_data_ring[9*i + 1] = outerradius*sin(i*angle);  
        vertex_buffer_data_ring[9*i + 2] = width; 

        vertex_buffer_data_ring[9*i + 3] = outerradius*cos(i*angle); 
        vertex_buffer_data_ring[9*i + 4] = innerradius*sin(i*angle);
        vertex_buffer_data_ring[9*i + 5] = 0.0f;
        
        vertex_buffer_data_ring[9*i + 6] = outerradius*cos((i+1)*angle); 
        vertex_buffer_data_ring[9*i + 7] = outerradius*sin((i+1)*angle); 
        vertex_buffer_data_ring[9*i + 8] = 0.0f;
    }
    for(int i =400; i < sides+400; i++)
    {
        vertex_buffer_data_ring[9*i] = outerradius*cos((i+1)*angle);
        vertex_buffer_data_ring[9*i + 1] = outerradius*sin((i+1)*angle);  
        vertex_buffer_data_ring[9*i + 2] = 0.0f;

        vertex_buffer_data_ring[9*i + 3] = outerradius*cos(i*angle); 
        vertex_buffer_data_ring[9*i + 4] = outerradius*sin(i*angle);
        vertex_buffer_data_ring[9*i + 5] = width;

        vertex_buffer_data_ring[9*i + 6] = outerradius*cos((i+1)*angle); 
        vertex_buffer_data_ring[9*i + 7] = outerradius*sin((i+1)*angle); 
        vertex_buffer_data_ring[9*i + 8] = width;
    }
    for(int i =500; i < sides+500; i++)
    {
        vertex_buffer_data_ring[9*i] = innerradius*cos((i+1)*angle);
        vertex_buffer_data_ring[9*i + 1] = innerradius*sin((i+1)*angle);  
        vertex_buffer_data_ring[9*i + 2] = 0.0f;

        vertex_buffer_data_ring[9*i + 3] = outerradius*cos(i*angle); 
        vertex_buffer_data_ring[9*i + 4] = outerradius*sin(i*angle);
        vertex_buffer_data_ring[9*i + 5] = 0.0f;

        vertex_buffer_data_ring[9*i + 6] = outerradius*cos((i+1)*angle); 
        vertex_buffer_data_ring[9*i + 7] = outerradius*sin((i+1)*angle); 
        vertex_buffer_data_ring[9*i + 8] = 0.0f;
    }
    this->top = create3DObject(GL_TRIANGLES, 6*sides*3, vertex_buffer_data_ring, COLOR_BLACK, GL_FILL);
}

void Cannon_Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate_pitch = glm::rotate((float) (-this->pitch * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate_yaw = glm::rotate((float) (this->yaw * M_PI / 180.0f), glm::vec3(0, 1, 0));

    Matrices.model *= (translate*rotate_yaw*rotate_pitch);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->top);
}

void Cannon_Missile::movement() {
    this->position.x += this->d.x;
    this->position.y += this->d.y ;
    this->position.z += this->d.z ;
}