#include <cstdlib>
#include <math.h>
#include <GL/glfw.h>

#ifdef __WIN32__
    #include "windows.h"
#endif // __WIN32__s

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif


///Даниел Делчев
///Компютърни Науки
///2 курс 2 поток 8 група  факултетен номер: 81211


///Домашно 1 по ОКГ  -  kanji



bool running()
{
    return( !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam( GLFW_OPENED) );
}

void init()
{
    int width, height;

    glfwInit();
    if( !glfwOpenWindow( 640, 480, 0, 0, 0, 0, 8, 0, GLFW_WINDOW ) ) return;

    glfwGetWindowSize( &width, &height );
    height = height > 0 ? height : 1;

    glViewport( 0, 0, width, height );
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 65.0f, (GLfloat)width/(GLfloat)height, 1.0f, 100.0f );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(0.2f, -1.0f, 10.0f,
    0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f );
}

void finit()
{
    glfwTerminate();
}


//чертае правоъгален паралелепипед
void DrawLine(float Cx,float Cy, float Cz,float height,float width,float length,float normal_vector_length){

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_POINT_SIZE);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(3);
    //this draws the "straight line"
    glBegin(GL_TRIANGLES);
        //draws bottom side -Z
        glNormal3f(0,0,-1*normal_vector_length);
        glVertex3f( Cx+(length/2),Cy+(width/2),Cz+0);//top left corner
        glVertex3f( Cx+(length/2),Cy-(width/2),Cz+0);//bottom left corner
        glVertex3f( Cx-(length/2),Cy+(width/2),Cz+0);//top right corner

        glVertex3f( Cx-(length/2),Cy-(width/2),Cz+0);//bottom right corner
        glVertex3f( Cx+(length/2),Cy-(width/2),Cz+0);//bottom left left corner
        glVertex3f( Cx-(length/2),Cy+(width/2),Cz+0);//top right corner

        //draws top side +Z
        glNormal3f(0,0,1*normal_vector_length);
        glVertex3f( Cx+(length/2),Cy+(width/2),Cz+height);
        glVertex3f( Cx+(length/2),Cy-(width/2),Cz+height);
        glVertex3f( Cx+-(length/2),Cy+(width/2),Cz+height);

        glVertex3f( Cx-(length/2),Cy-(width/2),Cz+height);
        glVertex3f( Cx+(length/2),Cy-(width/2),Cz+height);
        glVertex3f( Cx-(length/2),Cy+(width/2),Cz+height);

        //draws short side from +X
        glNormal3f(1*normal_vector_length,0,0);
        glVertex3f( Cx+(length/2),Cy+(width/2),Cz+0);//top left corner
        glVertex3f( Cx+(length/2),Cy-(width/2),Cz+0);//bottom left corner
        glVertex3f( Cx+(length/2),Cy-(width/2),Cz+height);//bottom left corner + h

        glVertex3f( Cx+(length/2),Cy-(width/2),Cz+height);//bottom left corner + h
        glVertex3f( Cx+(length/2),Cy+(width/2),Cz+height);//bottom left corner + h
        glVertex3f( Cx+(length/2),Cy+(width/2),Cz+0);//top left corner

        //draws short side from -X
        glNormal3f(-1*normal_vector_length,0,0);
        glVertex3f( Cx-(length/2),Cy+(width/2),Cz+0);//top left corner
        glVertex3f( Cx-(length/2),Cy-(width/2),Cz+0);//bottom left corner
        glVertex3f( Cx-(length/2),Cy-(width/2),Cz+height);//bottom left corner + h

        glVertex3f( Cx-(length/2),Cy-(width/2),Cz+height);//bottom left corner + h
        glVertex3f( Cx-(length/2),Cy+(width/2),Cz+height);
        glVertex3f( Cx-(length/2),Cy+(width/2),Cz+0);//top left corner

        //draws long side from Y
        glNormal3f(0,1*normal_vector_length,0);
        glVertex3f( Cx-(length/2),Cy+(width/2),Cz+height);//top left corner +h
        glVertex3f( Cx-(length/2),Cy+(width/2),Cz+0);//top left corner
        glVertex3f( Cx+(length/2),Cy+(width/2),Cz+0);//top right corner

        glVertex3f( Cx+(length/2),Cy+(width/2),Cz+0);//top right corner
        glVertex3f( Cx+(length/2),Cy+(width/2),Cz+height);//top right corner +h
        glVertex3f( Cx-(length/2),Cy+(width/2),Cz+height);//top left corner +h

        //draws long side from -Y
        glNormal3f(0,-1*normal_vector_length,0);
        glVertex3f( Cx-(length/2),Cy-(width/2),Cz+height);//top left corner +h
        glVertex3f( Cx-(length/2),Cy-(width/2),Cz+0);//top left corner
        glVertex3f( Cx+(length/2),Cy-(width/2),Cz+0);//top right corner

        glVertex3f( Cx+(length/2),Cy-(width/2),Cz+0);//top right corner
        glVertex3f( Cx+(length/2),Cy-(width/2),Cz+height);//top right corner +h
        glVertex3f( Cx-(length/2),Cy-(width/2),Cz+height);//top left corner +h
    glEnd();

}

//should be given only angles from 0 to 360 higher would break it
//Cx -абсциса на центъра
//Cy -ордината на центъра
//Cz -апликата на центура
//r1- единищ радиус r2-втори радиус
//alpha-начален ъгъл в градуси [0-360] beta-краен ъгъл в градуси [0-360]
//points- брой точки
//width- ширина
//height- височина
//light_length- дължина на вектора по подразбиране си е 1
//light_back и light_front са да кажат дали да се осветяват капачетата със сметнат нормалнен вектор или директно с (0,0,+-1) ако почва от 90 градуса
//exception 1,2 обръщат посоката на нормалния вектор ако са true
void DrawElipseCurve(float Cx,float Cy,float Cz,float r1,float r2,float alpha,float beta,int points_count,float width,float height,float light_length,bool light_back,bool light_front,bool exception1,bool exception2){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_POINT_SIZE);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(3);

    float starting_angle=alpha/180*M_PI;
    float ending_angle=beta/180*M_PI;
    float step=(fabs(ending_angle-starting_angle))/points_count;

    //short side beginning
    if ((fabs(alpha-beta))!=360){
        glBegin(GL_TRIANGLES);
            if (!light_front){
                glNormal3f(0,1*light_length,0);
            }
            else{
                float a1= -height*(r1*cos(starting_angle)-(r2-width)*cos(starting_angle));
                float b1= height*(r1*sin(starting_angle)-(r2-width)*sin(starting_angle));
                float c1=0;
                float length1=sqrt(a1*a1+b1*b1+c1*c1);
                if (exception1){
                 glNormal3f(-light_length*a1/length1,-light_length*b1/length1,-light_length*c1/length1);
                }
                else{
                    glNormal3f(light_length*a1/length1,light_length*b1/length1,light_length*c1/length1);
                }
            }
            glVertex3f(Cx+r1*sin(starting_angle),Cy+r2*cos(starting_angle),Cz);
            glVertex3f(Cx+(r1-width)*sin(starting_angle),Cy+(r2-width)*cos(starting_angle),Cz);
            glVertex3f(Cx+r1*sin(starting_angle),Cy+r2*cos(starting_angle),Cz+height);

            glVertex3f(Cx+r1*sin(starting_angle),Cy+r2*cos(starting_angle),Cz+height);
            glVertex3f(Cx+(r1-width)*sin(starting_angle),Cy+(r2-width)*cos(starting_angle),Cz+height);
            glVertex3f(Cx+(r1-width)*sin(starting_angle),Cy+(r2-width)*cos(starting_angle),Cz);
        glEnd();
    }

    //curves
    for (int i=0;i<points_count;i++){
        glBegin(GL_TRIANGLES);//
                    float a=-height*(r2*cos(starting_angle+step)-r2*cos(starting_angle));
                    float b=height*(r1*sin(starting_angle+step)-r1*sin(starting_angle));
                    float c=0;
                    float length=sqrt(a*a+b*b+c*c);
                    glNormal3f(light_length*a/length,light_length*b/length,light_length*c/length);

            // отвън
            glVertex3f(Cx+r1*sin(starting_angle),Cy+r2*cos(starting_angle),Cz);
            glVertex3f(Cx+r1*sin(starting_angle),Cy+r2*cos(starting_angle),Cz+height);
            glVertex3f(Cx+r1*sin(starting_angle+step),Cy+r2*cos(starting_angle+step),Cz+height);
                                                                /////
            glVertex3f(Cx+r1*sin(starting_angle+step),Cy+r2*cos(starting_angle+step),Cz+height);
            glVertex3f(Cx+r1*sin(starting_angle+step),Cy+r2*cos(starting_angle+step),Cz);
            glVertex3f(Cx+r1*sin(starting_angle),Cy+r2*cos(starting_angle),Cz);
                                                            ////

            //отвътре
            glNormal3f(-light_length*a/length,-light_length*b/length,-light_length*c/length);

            glVertex3f(Cx+(r1-width)*sin(starting_angle),Cy+(r2-width)*cos(starting_angle),Cz);
            glVertex3f(Cx+(r1-width)*sin(starting_angle),Cy+(r2-width)*cos(starting_angle),Cz+height);
            glVertex3f(Cx+(r1-width)*sin(starting_angle+step),Cy+(r2-width)*cos(starting_angle+step),Cz+height);
                                                                            //////
            glVertex3f(Cx+(r1-width)*sin(starting_angle+step),Cy+(r2-width)*cos(starting_angle+step),Cz+height);
            glVertex3f(Cx+(r1-width)*sin(starting_angle+step),Cy+(r2-width)*cos(starting_angle+step),Cz);
            glVertex3f(Cx+(r1-width)*sin(starting_angle),Cy+(r2-width)*cos(starting_angle),Cz);

            //отгоре
            glNormal3f(0,0,1*light_length);
            glVertex3f(Cx+r1*sin(starting_angle),Cy+r2*cos(starting_angle),Cz+height);
            glVertex3f(Cx+r1*sin(starting_angle+step),Cy+r2*cos(starting_angle+step),Cz+height);
            glVertex3f(Cx+(r1-width)*sin(starting_angle+step),Cy+(r2-width)*cos(starting_angle+step),Cz+height);


            glVertex3f(Cx+(r1-width)*sin(starting_angle+step),Cy+(r2-width)*cos(starting_angle+step),Cz+height);
            glVertex3f(Cx+(r1-width)*sin(starting_angle),Cy+(r2-width)*cos(starting_angle),Cz+height);
            glVertex3f(Cx+r1*sin(starting_angle),Cy+r2*cos(starting_angle),Cz+height);
            //отдоло

            glNormal3f(0,0,-1*light_length);
            glVertex3f(Cx+r1*sin(starting_angle),Cy+r2*cos(starting_angle),Cz);
            glVertex3f(Cx+r1*sin(starting_angle+step),Cy+r2*cos(starting_angle+step),Cz);
            glVertex3f(Cx+(r1-width)*sin(starting_angle+step),Cy+(r2-width)*cos(starting_angle+step),Cz);


            glVertex3f(Cx+(r1-width)*sin(starting_angle+step),Cy+(r2-width)*cos(starting_angle+step),Cz);
            glVertex3f(Cx+(r1-width)*sin(starting_angle),Cy+(r2-width)*cos(starting_angle),Cz);
            glVertex3f(Cx+r1*sin(starting_angle),Cy+r2*cos(starting_angle),Cz);
        glEnd();
        starting_angle+=step;
    }

    //short side end
    if ((fabs(alpha-beta))!=360){
        glBegin(GL_TRIANGLES);
        if (!light_back){
            glNormal3f(0,1*light_length,0);
        }
        else{
                float a2=height*width*cos(starting_angle);
                float b2=height*width*sin(starting_angle);
                float c2=0;
                float length2=sqrt(a2*a2+b2*b2+c2*c2);
                if (exception2){
                    glNormal3f(-light_length*a2/length2,-light_length*b2/length2,-light_length*c2/length2);
                }
                else{
                    glNormal3f(light_length*a2/length2,light_length*b2/length2,light_length*c2/length2);
                }
        }
            glVertex3f(Cx+r1*sin(starting_angle),Cy+r2*cos(starting_angle),Cz);
            glVertex3f(Cx+(r1-width)*sin(starting_angle),Cy+(r2-width)*cos(starting_angle),Cz);
            glVertex3f(Cx+r1*sin(starting_angle),Cy+r2*cos(starting_angle),Cz+height);

            glVertex3f(Cx+r1*sin(starting_angle),Cy+r2*cos(starting_angle),Cz+height);
            glVertex3f(Cx+(r1-width)*sin(starting_angle),Cy+(r2-width)*cos(starting_angle),Cz+height);
            glVertex3f(Cx+(r1-width)*sin(starting_angle),Cy+(r2-width)*cos(starting_angle),Cz);
        glEnd();
    }
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    const float GLOBAL_CENTER_X=0;
    const float GLOBAL_CENTER_Y=-1;
    const float GLOBAL_CENTER_Z=0;
    const float height=2;
    const float width=0.5; //широчината !! НЕ !! подлежи на промяна
    const float global_normal_vector_length=1.0;


void drawBottomPart(const float& X, const float& Y,const float& Z){
    DrawLine(X-0.065,Y-0.25,Z+0,height,width,7.0,global_normal_vector_length); //чертае призмата
    DrawElipseCurve(X-12.25,Y+0.33,Z+0,12,4.0,88.0,137,200,width,height,global_normal_vector_length,true,true,false,false); //чертае лявата крива
    //тези 2те чертаят дясната крива и 2те са части от елипса
    // радиусите им са разменени и центъра на едната е преместен за да се слее с другата без разместване
    DrawElipseCurve(X+1.25,Y+0,Z+0,2.25,3.4,90,180,200,width,height,global_normal_vector_length,true,false,false,false);
    DrawElipseCurve(X+1.25,Y-1.15,Z+0,3.4,2.25,180,215,200,width,height,global_normal_vector_length,true,true,false,false);
}

void drawMiddlePart(const float& X, const float& Y,const float& Z){
    DrawLine(X-2.3,Y+1.7,Z+0,height,width,3.1,global_normal_vector_length);
    DrawLine(X-2.3,Y+1.7,Z+0,height,1.8,width,global_normal_vector_length);
    //за наколонената права няма функция и се чертае тук
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    //наколонената линия
    glBegin(GL_TRIANGLES);
    //bottom side
    glNormal3f(0,0,-1*global_normal_vector_length);
    glVertex3f(X-0.4,Y+0.8,Z+0);                                         //(-0.4,0.8,0)A1
    glVertex3f(X-0.4,Y+0.8+width,Z+0);                                  //(-0.4,0.8+width,0)B1
    glVertex3f(X-4.2,Y+0.1+width,Z+0);                                   //(-3.9,0.1,0)C1
                                                                    //(-4.2,0.1+width,0)D1
    glVertex3f(X-4.2,Y+0.1+width,Z+0);
    glVertex3f(X-0.4,Y+0.8,Z+0);
    glVertex3f(X-3.9,Y+0.1,Z+0);
    //top side
    glNormal3f(0,0,1*global_normal_vector_length);
    glVertex3f(X-0.4,Y+0.8,Z+height);
    glVertex3f(X-0.4,Y+0.8+width,Z+height);
    glVertex3f(X-4.2,Y+0.1+width,Z+height);

    glVertex3f(X-4.2,Y+0.1+width,Z+height);
    glVertex3f(X-0.4,Y+0.8,Z+height);
    glVertex3f(X-3.9,Y+0.1,Z+height);

    //back lid
    float length_v1=sqrt(pow(height*width,2)+0+0);
    glNormal3f(global_normal_vector_length*height*width/length_v1,global_normal_vector_length*0/length_v1,global_normal_vector_length*0/length_v1);
    glVertex3f(X-0.4,Y+0.8,Z+0);//A1
    glVertex3f(X-0.4,Y+0.8+width,Z+0);//B1
    glVertex3f(X-0.4,Y+0.8+width,Z+height);//B2

    glVertex3f(X-0.4,Y+0.8+width,Z+height);//B2
    glVertex3f(X-0.4,Y+0.8,Z+height);//A2
    glVertex3f(X-0.4,Y+0.8,Z+0);//A1
    //front lid
    float length_v2=sqrt(pow(height*width,2)+pow((0.3*height),2)+0);
    glNormal3f(-global_normal_vector_length*height*width/length_v2,-global_normal_vector_length*0.3*height/length_v2,-global_normal_vector_length*0/length_v2);
    glVertex3f(X-3.9,Y+0.1,Z+0);                                //C1
    glVertex3f(X-4.2,Y+0.1+width,Z+0);                                //D1
    glVertex3f(X-4.2,Y+0.1+width,Z+height);                                //D2

    glVertex3f(X-4.2,Y+0.1+width,Z+height);                                //D2
    glVertex3f(X-3.9,Y+0.1,Z+height);                                //C2
    glVertex3f(X-3.9,Y+0.1,Z+0);                                //C1

    //smaller side

    float length_v3=sqrt(pow(0.7*height,2)+pow(3.5*height,2)+0);
    glNormal3f(-global_normal_vector_length*(-0.7)*height/length_v3,-global_normal_vector_length*(3.5)*height/length_v3,-global_normal_vector_length*0/length_v3);
    glVertex3f(X-3.9,Y+0.1,Z+0);             //C1
    glVertex3f(X-3.9,Y+0.1,Z+height);                    //C2
    glVertex3f(X-0.4,Y+0.8,Z+0);                      //B1

    glVertex3f(X-0.4,Y+0.8,Z+0);                       //B1
    glVertex3f(X-0.4,Y+0.8,Z+height);                      //B2
    glVertex3f(X-3.9,Y+0.1,Z+height);                   //C2

    //bigger side
    float length_v4=sqrt(pow(((-0.7)*height),2)+pow((3.8*height),2)+0);
    glNormal3f(global_normal_vector_length*(-0.7)*height/length_v4,global_normal_vector_length*(3.8)*height/length_v4,global_normal_vector_length*0/length_v4);
    glVertex3f(X-4.2,Y+0.1+width,Z+0);                                    //D1
    glVertex3f(X-4.2,Y+0.1+width,Z+height);                                        //D2
    glVertex3f(X-0.4,Y+0.8+width,Z+0);                                            //A1

    glVertex3f(X-0.4,Y+0.8+width,Z+0);                                             //A1
    glVertex3f(X-0.4,Y+0.8+width,Z+height);                                          //A2
    glVertex3f(X-4.2,Y+0.1+width,Z+height);                                         //D2
    glEnd();
}

void drawTopLeftPart(const float& X, const float& Y,const float& Z){
    DrawLine(X-2.3,Y+4.4-0.2,Z+0,height,width,3.1,global_normal_vector_length);
    DrawLine(X-2.3,Y+4.4,Z+0,height,1.3,width,global_normal_vector_length);
    DrawLine(X-2.3,Y+3.7,Z+0,height,0.4,width,global_normal_vector_length);
    DrawLine(X-2.3,Y+4.4-1,Z+0,height,width,3.9,global_normal_vector_length);
    //от тези се получава дпсното "ченгелче"
    float Cx=-0.9;
    float Cy=3;
    float Cz=0;
    DrawElipseCurve(X+Cx+0,Y+Cy+0,Z+Cz+0,0.8,0.8,100,180,200,width,height,global_normal_vector_length,false,true,false,false);
    DrawLine(X+Cx-0.20,Y+Cy-0.55,Z+Cz+0,height,width,0.4,global_normal_vector_length);
    DrawElipseCurve(X+Cx-0.4,Y+Cy+0,Z+Cz+0,0.8,0.8,180,270,200,width,height,global_normal_vector_length,false,false,false,false);
    DrawLine(X+Cx-0.95,Y+Cy+0.3,Z+Cz+0,height,0.6,0.5,global_normal_vector_length);

    //лявото "ченгелче"
    DrawElipseCurve(X-8.5,Y+3.4,Z+0,6,2.45,90,132,200,width,height,global_normal_vector_length,true,false,false,false);
}

void drawTopRightPart(const float& X, const float& Y,const float& Z){
    DrawLine(X+1.35,Y+3.75,Z+0,height,width,3.0,global_normal_vector_length);
    DrawElipseCurve(X+3.3,Y+4,Z,0.9,3.7,120,270,200,width,height,global_normal_vector_length,false,true,true,false);
    DrawLine(X+1.40,Y+4.5,Z+0,height,1,width,global_normal_vector_length);
    DrawElipseCurve(X-0.75,Y+3.5,Z+0,2.4,3.0,90,170,200,width,height,global_normal_vector_length,true,false,false,false);
    DrawElipseCurve(X-1.5,Y+1.5,Z+0,4.2,1.8,22.5,70,200,width,height,global_normal_vector_length,true,true,false,true);
}

int main()
{

    #ifdef __WIN32__
    FreeConsole();
    #endif // __WIN32__

    init();

    glClearColor( 0.45f, 0.45f, 0.45f, 0.82f );
    glEnable( GL_DEPTH_TEST );

    while( running() )
    {
        glClear( GL_COLOR_BUFFER_BIT+GL_DEPTH_BUFFER_BIT );

        glRotatef( 0.4, 3.5, -2.5, -5.0);


        glColor3ub(190,170,10);
        drawBottomPart(GLOBAL_CENTER_X,GLOBAL_CENTER_Y,GLOBAL_CENTER_Z);
        drawMiddlePart(GLOBAL_CENTER_X,GLOBAL_CENTER_Y,GLOBAL_CENTER_Z);
        drawTopLeftPart(GLOBAL_CENTER_X,GLOBAL_CENTER_Y,GLOBAL_CENTER_Z);
        drawTopRightPart(GLOBAL_CENTER_X,GLOBAL_CENTER_Y,GLOBAL_CENTER_Z);


        glfwSwapBuffers();
    }

    finit();
    return 0;
}
