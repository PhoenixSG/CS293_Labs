#include <simplecpp>

int main()
{
    int w = 1000;
    int h = 800;
    initCanvas("test", w, h);

    double x, y;
    double range_x = 4, range_y = 4;

    Rectangle r(0, 0, 1, 1);
    for (int i = 0; i <= h; i += 1)
    {
        for (int j = 0; j <= w; j += 1)
        {

            x = 2.0 * j / w * range_x - range_x;
            y = 2.0 * i / h * range_y - range_y;
            // cout<<x<<" "<<y<<endl;
            double x_1 = x, y_1 = y;
            int l;
            for (l = 0; l < 100; l++)
            {
                int real = x * x - y * y;
                int imag = 2 * x * y;

                x = real + x_1;
                y = imag + y_1;

                if (abs(x)+abs(y) > 10)
                {
                    break;
                }
            }

            if (l == 100)
            {
                r.setColor(COLOR("black"));
            }
            else
            {
                r.setColor(COLOR("red"));
            }

            r.moveTo(j, i);
            r.setFill();
            r.imprint();
        
        }
    }
    getClick();
    return 0;
}