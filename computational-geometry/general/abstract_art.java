// polygon boolean operations (Java magic library)
// https://open.kattis.com/problems/abstractart
// 2017 East-Central NA Regional

import java.util.*;
import java.io.*;
import java.awt.Polygon;
import java.awt.geom.Area;
import java.awt.geom.PathIterator;  

public class Main
{
    public static double area(Area ar)  {
        double acc = 0.0;
        double curr_x, curr_y;
        double prev_x = -1, prev_y = -1; // arbitrary initial values; won't be used
        double first_x = -1, first_y = -1; // ditto
        for (var it = ar.getPathIterator(null); !it.isDone(); it.next()) {
            double[] buffer = new double[6];
            int segType = it.currentSegment(buffer);
            if (segType == PathIterator.SEG_CLOSE) { // close the current loop
                curr_x = first_x;
                curr_y = first_y;
            } else {
                curr_x = buffer[0];
                curr_y = buffer[1];
            }
            if (segType != PathIterator.SEG_MOVETO) {
                acc += prev_x * curr_y - prev_y * curr_x;
            } else { // store the first point on the new loop
                first_x = curr_x;
                first_y = curr_y;
            }
            prev_x = curr_x;
            prev_y = curr_y;
        }
        return Math.abs(acc) / 2;
    }
    public static void main(String[] args) throws IOException {
        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(input.readLine());
        double totalPaint = 0;
        Area canvasArea = null;
        for(int it = 0; it < n; it++) {
            StringTokenizer st = new StringTokenizer(input.readLine());
            int m = Integer.parseInt(st.nextToken());
            int[] x = new int[m];
            int[] y = new int[m];
            for(int i = 0; i < m; i++) {
                x[i] = Integer.parseInt(st.nextToken());
                y[i] = Integer.parseInt(st.nextToken());
            }
            Polygon p = new Polygon(x,y,m);
            Area a = new Area(p);
            
            if (it == 0) canvasArea = a;
            else canvasArea.add(a);
            
            totalPaint += area(a);
        }
        out.println(totalPaint + " " + area(canvasArea));
        out.flush();
        out.close();
    }
}
