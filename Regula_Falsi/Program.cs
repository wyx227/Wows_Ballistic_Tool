using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


namespace Regula_Falsi
{
    class Program
    {
        double f(double x)
        {
            return Math.Cos(x) - x * Math.Exp(x);
        }
        static void regula (float x, float x0, float x1, float y0, float y1, int itr)
        {
            x = x0 - ((x1 - x0) / (y1 - y0)) * y0;
            ++(itr);

        }
        static void algorithmus()
        {
            do
            {

            } while (itr < 20);
        }
        static void Main(string[] args)
        {
        }
    }
}
