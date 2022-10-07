// イメージ：TeaPotの中に砂糖が入っていて、お茶を注いでいる

// GLUTの非対応メッセージを無効にする
// 正式にサポートしておらず、メッセージを出すものを無視する
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

// ヘッダファイル呼ばれるファイルを読み込む
#include <iostream>
// OpenGL.hに書かれている便利な命令を使う
#include <OpenGL/OpenGL.h>
// GLUT.hに書かれている便利な命令を使う
#include <GLUT/GLUT.h>

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
                   30,                      //視点の位置
                   (double)width/height,    //目標の位置
                   //見る体積の表面上の点
                   1.0,                     //前方面
                   100.0                    //後方面
                   );
                                                            
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
              //②視点の設定 モデルビュー行列
              //視点のカメラがあってどの方向を向くか
              5.0,5.0,10.0,    //視点の位置
              0.0,0.0,0.0,      //目標の位置
              0.0,1.0,1.0       //頭上方向
              );
                                                            
}

void display(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    
    //①三次元空間の座標指定
    //（頂点の座標値、接続情報,3次元の物体描画）
    glutWireCube(1.0);
    glColor3f(1.0, 0.0, 1.0);
    glutWireTeapot(3.0);
    
                                        
    glFlush();
}


int main(int argc, char ** argv) {
    glutInit(&argc, argv);              //intialize glut
    glutInitWindowSize(900, 500);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow("Hello 3d world");       // buildされた時の画面に表示される名前
    glutReshapeFunc(reshape);           // ウィンドウの処理
    glutDisplayFunc(display);           //display関数を別で作るためのここで名前を書いておく
    glutMainLoop();
    return 0;
}

//glutから始まるものは全てGLUT.hの便利な機能を使っている
