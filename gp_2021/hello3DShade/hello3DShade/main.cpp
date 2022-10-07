//
//  main.cpp
//  hello3DShade
//
//  Created by TomoHirata on 2021/05/20.
//  光源の調整によって見え方が変わるが、設定の仕方が慣れないうちは難しい

// GLUTの非対応メッセージを無効にする
// 正式にサポートしておらず、メッセージを出すものを無視する
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

// ヘッダファイル呼ばれるファイルを読み込む
#include <iostream>
// OpenGL.hに書かれている便利な命令を使う
#include <OpenGL/OpenGL.h>
// GLUT.hに書かれている便利な命令を使う
#include <GLUT/GLUT.h>

//光源の情報は様々な関数の中で使う
//Global Variables
//const GLfloat lightPosition[4] = {5.25, 2.0, 0.25, 1.0};
// 光の座標値                      x,y,z,w
// GL_LIGHT0
float lightPosition[4] = {5.25, 2.0, 0.25, 1.0};
// 環境光(Ambient)
float teapotAmbient[4] = {0.3, 0.5, 0.0, 1.0};
// 拡散反射光(Diffuse)
float teapotDiffuse[4] = {1.0, 1.0, 0.3, 1.0};
// 鏡面反射光(Specular)
float teapotSpecular[4] = {1.0, 1.0, 1.0, 1.0};
// 光具合 値が大きいほど光が強くなる、値が小さいとぼやける
float teapotShininess[1] = {20.0};

//GL_LIGHT1
float lightPosition2[4] = {5.25, 5.0, 0.25, 1.0};
float teapotAmbient2[4] = {0.3, 0.5, 0.3, 1.0};
float teapotDiffuse2[4] = {1.0, 1.0, 0.3, 1.0};
float teapotSpecular2[4] = {1.0, 0.0, 1.0, 1.0};
float teapotShininess2[1] = {5.0};

//GL_LIGHT2
float lightPosition3[4] = {0.25, 20.0, 5.25, 1.0};
float teapotAmbient3[4] = {1.5, 0.5, 0.5, 1.0};
float teapotDiffuse3[4] = {1.0, 1.0, 0.3, 1.0};
float teapotSpecular3[4] = {1.0, 3.0, 1.0, 1.0};
float teapotShininess3[1] = {-10.0};

//  3次元の空間設定
//  width & height、ウィンドウのサイズが変わる、他のウィンドウが重なり自分を前に出すというイベント時に呼ばれる
//  3次元の投影情報をreshpaの中に書く
void reshape(int width, int height){
    glViewport(0, 0, width, height);                        //表示範囲の設定
                                                            //ヴューポートの設定（左下が原点）
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
                   //③視点の設定 投影行列
                   //どのように投影するか
                   10,                      //視点の位置
                   (double)width/height,    //目標の位置
                   //見る体積の表面上の点
                   1.0,                     //前方面
                   50.0                    //後方面
                   );
                                                            
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
              //②視点の設定 モデルビュー行列
              //視点のカメラがあってどの方向を向くか
              0.3,3.0,10.0,    //視点の位置
              0.0,0.0,0.0,      //目標の位置
              0.0,5.0,0.0       //頭上方向
              );
                                                            
}

void display(){
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    
    // 背景を描く際に奥行きも考慮する
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glColor3f(1.0, 1.0, 1.0); // colorは既に設定しているため
    
    //①三次元空間の座標指定
    //（頂点の座標値、接続情報,3次元の物体描画）
    // glutWireCube(1.0);
    // glColor3f(1.0, 0.0, 1.0);
    // glutSolidTeapot(0.5);
    glutSolidSphere(0.5, 100, 64);
    //glutSolidTorus(1.0,64.0,64,16);
    glBegin(GL_LINE_LOOP);
    
    glVertex2d(-0.6, -0.6);
    glVertex2d(0.6, -0.6);
    glVertex2d(0.6, 0.6);
    glVertex2d(-0.6, 0.6);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex2d(-0.7, -0.7);
    glVertex2d(0.7, -0.7);
    glVertex2d(0.7, 0.7);
    glVertex2d(-0.7, 0.7);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex2d(-0.8, -0.8);
    glVertex2d(0.8, -0.8);
    glVertex2d(0.8, 0.8);
    glVertex2d(-0.8, 0.8);
    glEnd();

    glFlush();
}

void setup(){
    glEnable(GL_DEPTH_TEST); //奥行き情報が有効化
 
    // 光源の有効化
    glEnable(GL_LIGHTING);
    
    //GL_LIGHT0
    // 1個目の光源の有効化(0〜も書けば複数の光源が有効になる）
    glEnable(GL_LIGHT0);
    // 最初に定義したlightPositionが渡され、light0の座標値として設定される
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glMaterialfv(GL_FRONT, GL_AMBIENT, teapotAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, teapotDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, teapotSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, teapotShininess);
    
    //GL_LIGHT1
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, teapotAmbient2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, teapotDiffuse2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, teapotSpecular2);
    glMaterialfv(GL_FRONT, GL_SHININESS, teapotShininess2);
    
    //GL_LIGHT2
    glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT2, GL_POSITION, lightPosition3);
    glMaterialfv(GL_FRONT, GL_AMBIENT, teapotAmbient3);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, teapotDiffuse3);
    glMaterialfv(GL_FRONT, GL_SPECULAR, teapotSpecular3);
    glMaterialfv(GL_FRONT, GL_SHININESS, teapotShininess3);
}
 


int main(int argc, char ** argv) {
    glutInit(&argc, argv);              //intialize glut
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH); // 奥行き情報を使うための初期化
    glutCreateWindow("Hello 3d world");       // buildされた時の画面に表示される名前
    glutReshapeFunc(reshape);           // ウィンドウの処理
    glutDisplayFunc(display);           //display関数を別で作るためのここで名前を書いておく
    
    setup();
    
    glutMainLoop();
    return 0;
}

//glutから始まるものは全てGLUT.hの便利な機能を使っている

