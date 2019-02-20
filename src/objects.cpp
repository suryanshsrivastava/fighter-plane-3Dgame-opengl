#include "objects.h"
#include "main.h"
#include "plane.h"

Ring::Ring(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->innerradius=10;
    this->outerradius=20;
    this->width=0.5f;

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
    
    this->object = create3DObject(GL_TRIANGLES, 6*sides*3, vertex_buffer_data_ring, COLOR_METAL, GL_LINE);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = glm::translate(glm::vec3(0, 0, 0)) * rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ring::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

Volcano::Volcano(float x, float z, float orientation) {
    this->position = glm::vec3(x, 0, z);
    this->rotation = 0;
    this->radius=50.0f;
    this->tipradius=0.1f;
    this->height = 50.0f;
    this->islandheight = 0.1*(float)(rand()%5);
    
    GLfloat vertex_buffer_data_island[] = {
        -50.0f, islandheight, 50.0f,
        -50.0f, islandheight, -50.0f,
        50.0f, islandheight, 50.0f,

        50.0f, islandheight, -50.0f,
        -50.0f, islandheight, -50.0f,
        50.0f, islandheight, 50.0f,

        0.0f, islandheight, -75.0f,
        -50.0f+(float)(rand()%50), islandheight, 50.0f,
        (float)(rand()%50), islandheight, 50.0f,

        0.0f, islandheight, -75.0f,
        -50.0f+(float)(rand()%50), islandheight, -50.0f,
        (float)(rand()%50), islandheight, -50.0f,

        -75.0f, islandheight, 0.0f, 
        -50.0f, islandheight, -50.0f+(float)(rand()%50),
        -50.0f, islandheight, (float)(rand()%50),

        75.0f, islandheight, 0.0f, 
        50.0f, islandheight, -50.0f+(float)(rand()%50),
        50.0f, islandheight, (float)(rand()%50),
    };
    this->island = create3DObject(GL_TRIANGLES, 3*6, vertex_buffer_data_island, COLOR_GROUND , GL_FILL);

    int sides = 100;
    float angle = (2*M_PIl)/sides;

    GLfloat vertex_buffer_data_mountain[900]; 

    for(int i =0; i < sides; i++)
    {
        vertex_buffer_data_mountain[9*i] = tipradius*radius*cos((i+1)*angle);
        vertex_buffer_data_mountain[9*i + 1] = height;  
        vertex_buffer_data_mountain[9*i + 2] = tipradius*radius*sin((i+1)*angle);

        vertex_buffer_data_mountain[9*i + 3] = radius*cos(i*angle); 
        vertex_buffer_data_mountain[9*i + 4] = 0.0f;
        vertex_buffer_data_mountain[9*i + 5] = radius*sin(i*angle);

        vertex_buffer_data_mountain[9*i + 6] = radius*cos((i+1)*angle); 
        vertex_buffer_data_mountain[9*i + 7] = 0.0f; 
        vertex_buffer_data_mountain[9*i + 8] = radius*sin((i+1)*angle);
    }
    this->mountain = create3DObject(GL_TRIANGLES, sides*3, vertex_buffer_data_mountain, COLOR_BROWN , GL_FILL);
    
    GLfloat vertex_buffer_data_lava[1800]; 

    for(int i =0; i < sides; i++)
    {
        vertex_buffer_data_lava[9*i] = 0.0f;
        vertex_buffer_data_lava[9*i + 1] = 0.0f;  
        vertex_buffer_data_lava[9*i + 2] = 0.0f;

        vertex_buffer_data_lava[9*i + 3] = tipradius*radius*cos(i*angle); 
        vertex_buffer_data_lava[9*i + 4] = height;
        vertex_buffer_data_lava[9*i + 5] = tipradius*radius*sin(i*angle);

        vertex_buffer_data_lava[9*i + 6] = tipradius*radius*cos((i+1)*angle); 
        vertex_buffer_data_lava[9*i + 7] = height; 
        vertex_buffer_data_lava[9*i + 8] = tipradius*radius*sin((i+1)*angle);
    }
    for(int i =100; i < sides+100; i++)
    {
        vertex_buffer_data_lava[9*i] = radius*cos((i)*angle);
        vertex_buffer_data_lava[9*i + 1] = 0.0f;  
        vertex_buffer_data_lava[9*i + 2] = radius*sin((i)*angle);   

        vertex_buffer_data_lava[9*i + 3] = tipradius*radius*cos(i*angle); 
        vertex_buffer_data_lava[9*i + 4] = height;
        vertex_buffer_data_lava[9*i + 5] = tipradius*radius*sin(i*angle);

        vertex_buffer_data_lava[9*i + 6] = tipradius*radius*cos((i+1)*angle); 
        vertex_buffer_data_lava[9*i + 7] = height; 
        vertex_buffer_data_lava[9*i + 8] = tipradius*radius*sin((i+1)*angle);
    }
    this->lava = create3DObject(GL_TRIANGLES, 2*sides*3, vertex_buffer_data_lava, COLOR_ORANGE , GL_FILL);
}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = glm::translate(glm::vec3(0, 0, 0)) * rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->mountain);
    draw3DObject(this->lava);
    draw3DObject(this->island);
}