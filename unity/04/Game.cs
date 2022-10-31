#nullable enable
using GameCanvas;
using Unity.Mathematics;
using UnityEngine;
using UnityEngine.InputSystem;

/// <summary>
/// ゲームクラス。
/// </summary>
public sealed class Game : GameBase
{   
    // 変数の宣言
    // ボール用
    const int BALL_NUM = 30;
    int[] ball_x = new int [BALL_NUM]; // ボールのx座標
    int[] ball_y = new int [BALL_NUM]; // ボールのy座標
    int[] ball_col = new int [BALL_NUM];
    int[] ball_speed = new int [BALL_NUM]; // ボールの速度
    GcImage[] ball_img = new GcImage [BALL_NUM];
    int ball_w = 24;
    int ball_h = 24;

    // キャラクター用
    int player_x = 304; 
    int player_y = 448;
    int player_speed = 3;
    int player_w = 32;
    int player_h = 32;
    GcImage player_img = GcImage.GR0;

    // 得点と制限時間用
    int score = 0;
    int time = 1800;

    // プレイヤーの色、方向用
    int player_dir = 1;
    int player_col = 4;
    int combo = 0;

    /// <summary>
    /// 初期化処理
    /// </summary>
    public override void InitGame()
    {
        gc.SetResolution(640, 480);
        for (int i = 0; i < BALL_NUM; i++) {
            resetBall(i);
        }
    }

    /// <summary>
    /// 動きなどの更新処理
    /// </summary>
    public override void UpdateGame()
    {   
        // timeを1減らす;
        time = time - 1;

        // アニメーション処理を改変
        // 画面右半分を押したときの処理に1行追加
        player_dir = 1;
        // 画面左半分を押したときの処理に1行追加
        player_dir = -1;
        
        // 接触判定はballの移動処理あたり（for文で繰り返されるところ）に追加
        for (int i = 0; i < BALL_NUM; i++) {
            ball_y[i] = ball_y[i] + ball_speed[i];
            if (ball_y[i] > 480) {
                resetBall(i);
            }
            
            // ボールとキャラクターが接触しているかを判定
            // gc.CheckHitRect(ボールの座標、幅、高さ、プレイヤーの座標、幅、高さ)
            if (gc.CheckHitRect(player_x, player_y, player_w, player_h, ball_x[i], ball_y[i], ball_w, ball_h)) {
                if (time >= 0) {
                    // scoreをcolの値だけ足す
                    score += ball_col[i];

                    // ボールを取った時のスコア加算の後の処理
                    if (player_col == ball_col[i]) {
                        combo++;
                        score += combo;
                    }
                    else {
                        combo = 0;
                    }
                    player_col = ball_col[i];
                }
                // ボールの座標等をリセット（resetBallを呼ぶ）
                resetBall(i);
            }
        }

        // int gc.GetPointerFrameCount(int);
        // タッチされた瞬間からのフレーム数を返す
        // 押されていない時は0、押した瞬間は1が入る
        // 押し続けて居ると1フレーム毎に値が1増える
        // 引数は達ししたポイントのID(基本0を入れる)
        // 0以外を入れると、複数箇所をタッチした場合に
        // 2箇所目3箇所目等の各フレーム数を取得できる
        if (gc.GetPointerFrameCount(0) > 0) {
            // タッチされている場所のx座標を返す（GetPointerYもある）
            if (gc.GetPointerX(0) > 320) {

                // X方向にplayer_speedずつ進める
                player_x += player_speed;
                player_img = GcImage.GR0;
            }
            else {
                // プレイヤーの速度を反転させる
                player_x -= player_speed;
                player_img = GcImage.GL0;
            }
        }
    }

    /// <summary>
    /// 描画の処理
    /// </summary>
    public override void DrawGame()
    {
        // 画面をクリア
        gc.ClearScreen();

        for (int i = 0; i < BALL_NUM; i++) {
            // gc.DrawImage(GcImage img, int x, int y);
            // 座標x,yにGcImageの画像を表示
            // 画像は「GcImage.」にresフォルダの画像ファイル名を足して指定
            // 例：GcImage.BallYellow 
            gc.DrawImage(ball_img[i], ball_x[i], ball_y[i]);
        }

        // gc.DrawImage(player_img, player_x, player_y);
        // アニメーション処理を改変
        if (time >= 0) {
            drawCharacter(player_x, player_y, player_col, player_dir, (time%60>=15)?2:1);
        } 
        else {
            drawCharacter(player_x, player_y, player_col, player_dir, 3);
        }

        // gc.SetColor(int, int, int); // 描画色を指定(RGBの順で0~255を指定)
        gc.SetColor(0, 0, 0);
        if (time >= 0) {
            // 座標(x,y)に文字列を描画
            gc.DrawString("time: " + time, 0, 0);
        }
        else {
            gc.DrawString("finished!!", 0, 0);
        }

        // スコア表示
        gc.DrawString("score: " + score, 0, 24);

        // コンボ数表示
        gc.DrawString("combo: " + combo, 0, 48);
    }

    void drawCharacter(int x, int y, int col, int dir, int anim) {
        GcImage[] images = new []{
            GcImage.YR0, GcImage.YR1, GcImage.YR2, GcImage.YR3,
            GcImage.RR0, GcImage.RR1, GcImage.RR2, GcImage.RR3,
            GcImage.BR0, GcImage.BR1, GcImage.BR2, GcImage.BR3,
            GcImage.GR0, GcImage.GR1, GcImage.GR2, GcImage.GR3,
            GcImage.YL0, GcImage.YL1, GcImage.YL2, GcImage.YL3,
            GcImage.RL0, GcImage.RL1, GcImage.RL2, GcImage.RL3,
            GcImage.BL0, GcImage.BL1, GcImage.BL2, GcImage.BL3,
            GcImage.GL0, GcImage.GL1, GcImage.GL2, GcImage.GL3,
        };
        int img_num = 0;

        // colやanimやdirでimg_numの値を変える
        img_num = (col-1) * 4 + anim;
        if (dir == -1) img_num += 16;

        gc.DrawImage( images[img_num], x, y);
    }

    void resetBall(int id) {
        // gc.Random(int min, int max); // 最小値と最大値の中で、何れかの数値を返す
        // （サイコロを表現したい場合）：gc.Random(1,6);
        ball_x[id] = gc.Random(0, 616);
        ball_y[id] = -gc.Random(24, 480);
        ball_speed[id] = gc.Random(3, 6);
        ball_col[id] = gc.Random(1, 3);

        if (ball_col[id] == 1) {
            ball_img[id] = GcImage.BallYellow;
        }
        else if (ball_col[id] == 2) {
            ball_img[id] = GcImage.BallRed;
        }
        else {
            ball_img[id] = GcImage.BallBlue;
        }

    }
}
