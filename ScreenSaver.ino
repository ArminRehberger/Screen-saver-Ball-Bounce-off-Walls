
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 600
const double Pi = 3.1415926535897932384626433832795;

void setup()
{
  // ########## Serial Monitor
  Serial.begin(9600);
  while (!Serial && millis() < 1000) {} //wait for Serial Monitor
  Serial.println("Startup");
}

void loop()
{
  static unsigned long TimerScreensaverPreviousMillis = 0;
  static unsigned long TimerScreensaverCurrentMillis = 0;
  static bool RecalculatePositionScreensaver = false;
  typedef struct
  {
    double x;
    double y;
    double speed;
    double radius;
    double angle;
  } StructBall;
  static StructBall ball =    {200.0, 200.0, 10.0, 128.0, 0.5};

  // ########## Timer recalculate position image screensaver
  TimerScreensaverCurrentMillis = millis();
  if(TimerScreensaverCurrentMillis - TimerScreensaverPreviousMillis >= 100)
  {
    TimerScreensaverPreviousMillis = millis();
    RecalculatePositionScreensaver = true;
  }

  // ########## Recalculate position image screensaver
  if(RecalculatePositionScreensaver == true)
  {
    RecalculatePositionScreensaver = false;

    ball.x += cos(ball.angle) * ball.speed;
    ball.y += sin(ball.angle) * ball.speed;

    if(ball.x - ball.radius < 0.0) // ball hits left wall
    {
        ball.x = ball.radius;
        ball.angle = Pi - ball.angle;
    }
    else if(ball.x + ball.radius > SCREEN_WIDTH)// ball hits right wall
    {
        ball.x = SCREEN_WIDTH - ball.radius;
        ball.angle = Pi - ball.angle;
    }

    if(ball.y < ball.radius)// ball hits top wall
    {
        ball.y = ball.radius;
        ball.angle = (Pi * 2.0) - ball.angle;
    }
    else if(ball.y + ball.radius > SCREEN_HEIGHT)// ball hits bottom wall
    {
        ball.y = SCREEN_HEIGHT - ball.radius;
        ball.angle = (Pi * 2.0) - ball.angle;
    }

    // ##### Print position
    Serial.print("Angle ");
    Serial.println(ball.angle, DEC);

    Serial.print("ball.x ");
    Serial.println(ball.x, DEC);

    Serial.print("ball.y ");
    Serial.println(ball.y, DEC);
  }

}
