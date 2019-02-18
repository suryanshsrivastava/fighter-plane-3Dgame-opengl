#include "plane.h"
#include "main.h"

Plane::Plane(float x0, float y0, float z0, color_t color) {
    this->position = glm::vec3(x0, y0, z0);
    this->speed = 1;
    // this->rotation = 0;
    this->radius = 0.25;
    this->length = 2.5f;
    this->nose = 1.0f;
    this->engine = 0.25f;
    
    this->rise=0;
    this->yaw = 0;
    this->pitch = 0;
    this->tilt = 0;
    
    int sides = 100;
    float angle = (2*M_PIl)/sides;

    //Cockpit
    GLfloat vertex_buffer_data_cockpit[1800]; 
    
    for(int i = 0; i < sides; i++)
    {
        vertex_buffer_data_cockpit[9*i] = 0.5f*radius*cos(i*angle);
        vertex_buffer_data_cockpit[9*i + 1] = 0.5f*radius*sin(i*angle);  
        vertex_buffer_data_cockpit[9*i + 2] = nose + length + engine;

        vertex_buffer_data_cockpit[9*i + 3] = radius*cos(i*angle); 
        vertex_buffer_data_cockpit[9*i + 4] = radius*sin(i*angle);
        vertex_buffer_data_cockpit[9*i + 5] = length + engine;
        
        vertex_buffer_data_cockpit[9*i + 6] = radius*cos((i+1)*angle); 
        vertex_buffer_data_cockpit[9*i + 7] = radius*sin((i+1)*angle); 
        vertex_buffer_data_cockpit[9*i + 8] = length + engine;
    }
    for(int i = 100; i < sides+100; i++)
    {
        vertex_buffer_data_cockpit[9*i] = radius*cos((i+1)*angle);
        vertex_buffer_data_cockpit[9*i + 1] = radius*sin((i+1)*angle);  
        vertex_buffer_data_cockpit[9*i + 2] = length + engine;

        vertex_buffer_data_cockpit[9*i + 3] = 0.5f*radius*cos(i*angle); 
        vertex_buffer_data_cockpit[9*i + 4] = 0.5f*radius*sin(i*angle);
        vertex_buffer_data_cockpit[9*i + 5] = nose + length + engine;
        
        vertex_buffer_data_cockpit[9*i + 6] = 0.5f*radius*cos((i+1)*angle); 
        vertex_buffer_data_cockpit[9*i + 7] = 0.5f*radius*sin((i+1)*angle); 
        vertex_buffer_data_cockpit[9*i + 8] = nose + length + engine;
    }
    this->cockpit = create3DObject(GL_TRIANGLES, 2*sides*3, vertex_buffer_data_cockpit, color, GL_FILL);

    //Cyllinderical Body
    GLfloat vertex_buffer_data_body[2700]; 

    for(int i =0; i < sides; i++)
    {
        vertex_buffer_data_body[9*i] = radius*cos(i*angle);
        vertex_buffer_data_body[9*i + 1] = radius*sin(i*angle);  
        vertex_buffer_data_body[9*i + 2] = length + engine;
        
        vertex_buffer_data_body[9*i + 3] = radius*cos(i*angle); 
        vertex_buffer_data_body[9*i + 4] = radius*sin(i*angle);
        vertex_buffer_data_body[9*i + 5] = engine;

        vertex_buffer_data_body[9*i + 6] = radius*cos((i+1)*angle); 
        vertex_buffer_data_body[9*i + 7] = radius*sin((i+1)*angle); 
        vertex_buffer_data_body[9*i + 8] = engine;
    }
    for(int i =100; i < sides+100; i++)
    {
        vertex_buffer_data_body[9*i] = radius*cos((i+1)*angle);
        vertex_buffer_data_body[9*i + 1] = radius*sin((i+1)*angle);  
        vertex_buffer_data_body[9*i + 2] = engine;
        
        vertex_buffer_data_body[9*i + 3] = radius*cos(i*angle); 
        vertex_buffer_data_body[9*i + 4] = radius*sin(i*angle);
        vertex_buffer_data_body[9*i + 5] = length + engine;

        vertex_buffer_data_body[9*i + 6] = radius*cos((i+1)*angle); 
        vertex_buffer_data_body[9*i + 7] = radius*sin((i+1)*angle); 
        vertex_buffer_data_body[9*i + 8] = length + engine;
    }
    
    for(int i =200; i < sides+200; i++)
    {
        vertex_buffer_data_body[9*i] = 0.5*radius*cos((i+1)*angle);
        vertex_buffer_data_body[9*i + 1] = 0.5*radius*sin((i+1)*angle);  
        vertex_buffer_data_body[9*i + 2] = 0.0f;

        vertex_buffer_data_body[9*i + 3] = radius*cos(i*angle); 
        vertex_buffer_data_body[9*i + 4] = radius*sin(i*angle);
        vertex_buffer_data_body[9*i + 5] = engine;

        vertex_buffer_data_body[9*i + 6] = radius*cos((i+1)*angle); 
        vertex_buffer_data_body[9*i + 7] = radius*sin((i+1)*angle); 
        vertex_buffer_data_body[9*i + 8] = engine;
    }

    this->body = create3DObject(GL_TRIANGLES, 3*sides*3, vertex_buffer_data_body, COLOR_METAL, GL_FILL);

    GLfloat vertex_buffer_data_engine[1800]; 

    for(int i =0; i < sides; i++)
    {
        vertex_buffer_data_engine[9*i] = radius*cos(i*angle);
        vertex_buffer_data_engine[9*i + 1] = radius*sin(i*angle);  
        vertex_buffer_data_engine[9*i + 2] = engine;

        vertex_buffer_data_engine[9*i + 3] = 0.5f*radius*cos(i*angle); 
        vertex_buffer_data_engine[9*i + 4] = 0.5f*radius*sin(i*angle);
        vertex_buffer_data_engine[9*i + 5] = 0.0f;

        vertex_buffer_data_engine[9*i + 6] = 0.5f*radius*cos((i+1)*angle); 
        vertex_buffer_data_engine[9*i + 7] = 0.5f*radius*sin((i+1)*angle); 
        vertex_buffer_data_engine[9*i + 8] = 0.0f;
    }
    for(int i =100; i < sides+100; i++)
    {
        vertex_buffer_data_engine[9*i] = 0.0f;
        vertex_buffer_data_engine[9*i + 1] = 0.0f;  
        vertex_buffer_data_engine[9*i + 2] = 0.0f;

        vertex_buffer_data_engine[9*i + 3] = 0.5*radius*cos(i*angle); 
        vertex_buffer_data_engine[9*i + 4] = 0.5*radius*sin(i*angle);
        vertex_buffer_data_engine[9*i + 5] = 0.0f;

        vertex_buffer_data_engine[9*i + 6] = 0.5*radius*cos((i+1)*angle); 
        vertex_buffer_data_engine[9*i + 7] = 0.5*radius*sin((i+1)*angle); 
        vertex_buffer_data_engine[9*i + 8] = 0.0f;
    }
    this->fuel = create3DObject(GL_TRIANGLES, 2*sides*3, vertex_buffer_data_engine, COLOR_ORANGE , GL_FILL);

    // Wings
    float finwidth = 15.0f;
    float finlength = 6.0f;
    float finbreadth = 0.75f;
    float finstart = length + engine;
    GLfloat vertex_buffer_data_fin[9];
    for(int i =0; i < 2; i++)
    {
        vertex_buffer_data_fin[0 + 36*i] = radius*cos(glm::radians(finwidth + float(i)*360.0f/2.0f));
        vertex_buffer_data_fin[1 + 36*i] = radius*sin(glm::radians(finwidth + float(i)*360.0f/2.0f));
        vertex_buffer_data_fin[2 + 36*i] = finstart - finbreadth;

        vertex_buffer_data_fin[3 + 36*i] = radius*cos(glm::radians(finwidth + float(i)*360.0f/2.0f));
        vertex_buffer_data_fin[4 + 36*i] = radius*sin(glm::radians(finwidth + float(i)*360.0f/2.0f));
        vertex_buffer_data_fin[5 + 36*i] = finstart;

        vertex_buffer_data_fin[6 + 36*i] = finlength*radius*cos(glm::radians(0.0f + float(i)*360.0f/2.0f));
        vertex_buffer_data_fin[7 + 36*i] = finlength*radius*sin(glm::radians(0.0f + float(i)*360.0f/2.0f));
        vertex_buffer_data_fin[8 + 36*i] = finstart - finbreadth;
        

        vertex_buffer_data_fin[9 + 36*i] = radius*cos(glm::radians(-finwidth + float(i)*360.0f/2.0f));
        vertex_buffer_data_fin[10 + 36*i] = radius*sin(glm::radians(-finwidth + float(i)*360.0f/2.0f));
        vertex_buffer_data_fin[11 + 36*i] = finstart - finbreadth;

        vertex_buffer_data_fin[12 + 36*i] = radius*cos(glm::radians(-finwidth + float(i)*360.0f/2.0f ));
        vertex_buffer_data_fin[13 + 36*i] = radius*sin(glm::radians(-finwidth + float(i)*360.0f/2.0f));
        vertex_buffer_data_fin[14 + 36*i] = finstart;

        vertex_buffer_data_fin[15 + 36*i] = finlength*radius*cos(glm::radians(0.0f + float(i)*360.0f/2.0f));
        vertex_buffer_data_fin[16 + 36*i] = finlength*radius*sin(glm::radians(0.0f + float(i)*360.0f/2.0f));
        vertex_buffer_data_fin[17 + 36*i] = finstart - finbreadth;


        vertex_buffer_data_fin[18 + 36*i] = radius*cos(glm::radians(-finwidth + float(i)*360.0f/2.0f));
        vertex_buffer_data_fin[19 + 36*i] = radius*sin(glm::radians(-finwidth + float(i)*360.0f/2.0f));
        vertex_buffer_data_fin[20 + 36*i] = finstart;

        vertex_buffer_data_fin[21 + 36*i] = radius*cos(glm::radians(finwidth + float(i)*360.0f/2.0f));
        vertex_buffer_data_fin[22 + 36*i] = radius*sin(glm::radians(finwidth + float(i)*360.0f/2.0f));
        vertex_buffer_data_fin[23 + 36*i] = finstart;

        vertex_buffer_data_fin[24 + 36*i] = finlength*radius*cos(glm::radians(0.0f + float(i)*360.0f/2.0f));
        vertex_buffer_data_fin[25 + 36*i] = finlength*radius*sin(glm::radians(0.0f + float(i)*360.0f/2.0f));
        vertex_buffer_data_fin[26 + 36*i] = finstart - finbreadth;


        vertex_buffer_data_fin[27 + 36*i] = radius*cos(glm::radians(-finwidth + float(i)*360.0f/2.0f));
        vertex_buffer_data_fin[28 + 36*i] = radius*sin(glm::radians(-finwidth + float(i)*360.0f/2.0f));
        vertex_buffer_data_fin[29 + 36*i] = finstart - finbreadth;

        vertex_buffer_data_fin[30 + 36*i] = radius*cos(glm::radians(finwidth + float(i)*360.0f/2.0f));
        vertex_buffer_data_fin[31 + 36*i] = radius*sin(glm::radians(finwidth + float(i)*360.0f/2.0f));
        vertex_buffer_data_fin[32 + 36*i] = finstart - finbreadth;

        vertex_buffer_data_fin[33 + 36*i] = finlength*radius*cos(glm::radians(0.0f + float(i)*360.0f/2.0f));
        vertex_buffer_data_fin[34 + 36*i] = finlength*radius*sin(glm::radians(0.0f + float(i)*360.0f/2.0f));
        vertex_buffer_data_fin[35 + 36*i] = finstart - finbreadth;
    }
    this->fin = create3DObject(GL_TRIANGLES, 36*3, vertex_buffer_data_fin, COLOR_BLACK , GL_FILL);

    //Tail fin
    GLfloat vertex_buffer_data_tailfin[9];
    finlength *= 0.5f;
    finbreadth = 0.5f;
    finstart = engine + finbreadth;
    for(int i =0; i < 3; i++)
    {
        vertex_buffer_data_tailfin[0 + 36*i] = radius*cos(glm::radians(finwidth + float(i)*360.0f/4.0f));
        vertex_buffer_data_tailfin[1 + 36*i] = radius*sin(glm::radians(finwidth + float(i)*360.0f/4.0f));
        vertex_buffer_data_tailfin[2 + 36*i] = finstart - finbreadth;

        vertex_buffer_data_tailfin[3 + 36*i] = radius*cos(glm::radians(finwidth + float(i)*360.0f/4.0f));
        vertex_buffer_data_tailfin[4 + 36*i] = radius*sin(glm::radians(finwidth + float(i)*360.0f/4.0f));
        vertex_buffer_data_tailfin[5 + 36*i] = finstart;

        vertex_buffer_data_tailfin[6 + 36*i] = finlength*radius*cos(glm::radians(0.0f + float(i)*360.0f/4.0f));
        vertex_buffer_data_tailfin[7 + 36*i] = finlength*radius*sin(glm::radians(0.0f + float(i)*360.0f/4.0f));
        vertex_buffer_data_tailfin[8 + 36*i] = finstart - finbreadth;


        vertex_buffer_data_tailfin[9 + 36*i] = radius*cos(glm::radians(-finwidth + float(i)*360.0f/4.0f));
        vertex_buffer_data_tailfin[10 + 36*i] = radius*sin(glm::radians(-finwidth + float(i)*360.0f/4.0f));
        vertex_buffer_data_tailfin[11 + 36*i] = finstart - finbreadth;

        vertex_buffer_data_tailfin[12 + 36*i] = radius*cos(glm::radians(-finwidth + float(i)*360.0f/4.0f ));
        vertex_buffer_data_tailfin[13 + 36*i] = radius*sin(glm::radians(-finwidth + float(i)*360.0f/4.0f));
        vertex_buffer_data_tailfin[14 + 36*i] = finstart;

        vertex_buffer_data_tailfin[15 + 36*i] = finlength*radius*cos(glm::radians(0.0f + float(i)*360.0f/4.0f));
        vertex_buffer_data_tailfin[16 + 36*i] = finlength*radius*sin(glm::radians(0.0f + float(i)*360.0f/4.0f));
        vertex_buffer_data_tailfin[17 + 36*i] = finstart - finbreadth;


        vertex_buffer_data_tailfin[18 + 36*i] = radius*cos(glm::radians(-finwidth + float(i)*360.0f/4.0f));
        vertex_buffer_data_tailfin[19 + 36*i] = radius*sin(glm::radians(-finwidth + float(i)*360.0f/4.0f));
        vertex_buffer_data_tailfin[20 + 36*i] = finstart;

        vertex_buffer_data_tailfin[21 + 36*i] = radius*cos(glm::radians(finwidth + float(i)*360.0f/4.0f));
        vertex_buffer_data_tailfin[22 + 36*i] = radius*sin(glm::radians(finwidth + float(i)*360.0f/4.0f));
        vertex_buffer_data_tailfin[23 + 36*i] = finstart;

        vertex_buffer_data_tailfin[24 + 36*i] = finlength*radius*cos(glm::radians(0.0f + float(i)*360.0f/4.0f));
        vertex_buffer_data_tailfin[25 + 36*i] = finlength*radius*sin(glm::radians(0.0f + float(i)*360.0f/4.0f));
        vertex_buffer_data_tailfin[26 + 36*i] = finstart - finbreadth;


        vertex_buffer_data_tailfin[27 + 36*i] = radius*cos(glm::radians(-finwidth + float(i)*360.0f/4.0f));
        vertex_buffer_data_tailfin[28 + 36*i] = radius*sin(glm::radians(-finwidth + float(i)*360.0f/4.0f));
        vertex_buffer_data_tailfin[29 + 36*i] = finstart - finbreadth;

        vertex_buffer_data_tailfin[30 + 36*i] = radius*cos(glm::radians(finwidth + float(i)*360.0f/4.0f));
        vertex_buffer_data_tailfin[31 + 36*i] = radius*sin(glm::radians(finwidth + float(i)*360.0f/4.0f));
        vertex_buffer_data_tailfin[32 + 36*i] = finstart - finbreadth;

        vertex_buffer_data_tailfin[33 + 36*i] = finlength*radius*cos(glm::radians(0.0f + float(i)*360.0f/4.0f));
        vertex_buffer_data_tailfin[34 + 36*i] = finlength*radius*sin(glm::radians(0.0f + float(i)*360.0f/4.0f));
        vertex_buffer_data_tailfin[35 + 36*i] = finstart - finbreadth;
    }
    this->tailfin = create3DObject(GL_TRIANGLES, 36*3, vertex_buffer_data_tailfin, COLOR_BLACK , GL_FILL);
}

void Plane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate_yaw = glm::rotate((float) (this->yaw * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate_pitch = glm::rotate((float) (this->pitch * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate_roll = glm::rotate((float) (this->tilt * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate_yaw * rotate_pitch * rotate_roll);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->cockpit);
    draw3DObject(this->body);
    draw3DObject(this->fuel);
    draw3DObject(this->fin);
    draw3DObject(this->tailfin);
}

void Plane::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Plane::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

void Plane::move_rise() {
    this->rise = 0.2f;
    this->position.y += rise;
}

void Plane::gravity(bool gravity_effect) {
    if (gravity_effect) {
        if (this->position.y <= 0) {
            this->position.y = 0;
        }
        else{
            this->position.y += this->rise;
            this->rise -= 0.01f;
            printf("down\n");
        }
    }
}

void Plane::tick_yaw( bool clockwise ) {
    if(clockwise) {
        this->yaw -= 1;
    }
    else if (!clockwise) {
        this->yaw += 1;
    }
}

void Plane::tick_forward() {
    // this->position.z += this->speed*cos(this-> * M_PI / 180.0f);
    // this->position.y += this->speed*cos(this->yaw * M_PI / 180.0f);
    // this->position.x += this->speed*cos(this->yaw * M_PI / 180.0f);
}

void Plane::tick_roll( bool right) {
    if (right) {
        this->tilt += 1;
    }
    else if (!right) {
        this->tilt -= 1;
    } 
}