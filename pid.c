#include <stdio.h>

// controller構造体
typedef struct {
    double Kp;
    double Ki;
    double Kd;
    double prev_error;
    double integral;
    double out_min;
    double out_max;
} PIDController;

// コントローラの初期化関数
void pid_init(PIDController *pid, double Kp, double Ki, double Kd,
              double out_min, double out_max)
{
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->prev_error = 0.0;
    pid->integral = 0.0;
    pid->out_min = out_min;
    pid->out_max = out_max;
}

// 制御更新関数
double pid_update(PIDController *pid, double setpoint, double measurement, double dt)
{
    double error = setpoint - measurement;

    // 積分項更新
    pid->integral += error * dt;

    // 微分項（誤差の差分）
    double derivative = (error - pid->prev_error) / dt;

    double output = pid->Kp * error
                  + pid->Ki * pid->integral
                  + pid->Kd * derivative;

    // 出力飽和
    if (output > pid->out_max) {
        output = pid->out_max;
    } else if (output < pid->out_min) {
        output = pid->out_min;
    }

    pid->prev_error = error;

    return output;
}

int main(void)
{
    PIDController pid;
    pid_init(&pid, 1.0, 0.5, 0.1, -100.0, 100.0);  // とりあえずの値

    double dt = 0.01;      // 10ms周期（シミュレーション上）
    double tau = 0.5;      // 時定数
    double y = 0.0;        // 出力
    double r = 1.0;        // 目標値

    for (int k = 0; k < 1000; ++k) {
        double u = pid_update(&pid, r, y, dt);

        // 1次遅れモデルでyを更新
        double dy = (-y + u) / tau;
        y += dy * dt;

        printf("%f, %f, %f\n", k * dt, y, u); // time, output, control

        // 実時間に合わせたければsleepを入れる（シミュレーションだけなら不要）
    }

    return 0;
}
