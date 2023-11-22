#include "tgaimage.h"
#include "model.h"

#include "vector3.h"
#include "matrix3.h"
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

//0< m <1
//void lineBresenham_2(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
//    int dx = fabs(x1 - x0); int dy = fabs(y1 - y0);
//    int p0 = 2 * dy - dx;
//    int twoDy = 2 * dy; int twoDyMinusDx = 2 * (dy - dx);
//    int x, y;
//    //reflect dirction
//
//    if (x0 > x1)
//    {
//        x = x1;
//        y = y1;
//        x1 = x0;
//    }
//    else{
//        x = x0; y = y0;
//    }
//    //original point
//    image.set(x, y, color);
//
//    while (x < x1) {
//        x++;
//        //Move one grid right x first
//        if (p0 < 0) {
//            p0 += twoDy;
//        }
//        else
//        {
//            //over the line point
//            y++;
//            p0 += twoDyMinusDx;
//        }
//        image.set(x, y, color);
//    }
//}

//void lineBresenham_3(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
//    int dx = fabs(x1 - x0); int dy = fabs(y1 - y0);
//    int p0 = 2 * dy - dx;
//    int twoDy = 2 * dy; int twoDyMinusDx = 2 * (dy - dx);
//    int x, y;
//    bool steep = false;
//
//    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
//        std::swap(x0, y0);
//        std::swap(x1, y1);
//        steep = true;
//    }
//    if (x0 > x1) {
//        std::swap(x0, x1);
//        std::swap(y0, y1);
//    }
//    y = y0;
//    for (int x = x0; x <= x1; x++) {
//        if (steep){
//            image.set(y, x, color);
//            }
//        else {
//                image.set(x, y, color);
//            }           
//        if (p0 < 0) {
//            p0 += twoDy;
//        }
//        else{
//           y++;
//                   // y += (y1 > y0 ? 1 : -1);
//                    p0 += twoDyMinusDx;
//                }
//        }
//       }


//������ע�⵽��ÿ��ѭ���г����ĳ��� (x1 - x0) ������ͬ�ģ����ⲽ�����õ�ѭ���⡣
//error ������ʾ���ǵ�ǰ�������� (x, y) ������ֱ�ߵľ��� (�����ߵľ��룬�����Ǵ�ֱ����)��
//ÿ�� error ����һ�����صĳ��ȣ����ǽ� y ���� 1��ͬʱ�� error ��С 1�� 



void lineBresenham2(int x1, int y1, int x2, int y2, TGAImage& image, TGAColor color) {
    // ����б�ʵľ���ֵ���� 1 ��ֱ��
    bool steep = false;
    if (std::abs(x1 - x2) < std::abs(y1 - y2)) {
        std::swap(x1, y1);
        std::swap(x2, y2);
        steep = true;
    }
    // ��������յ������
    if (x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }
    int y = y1;
    int eps = 0;
    int dx = x2 - x1;
    int dy = y2 - y1;
    int yi = 1;

    // ���� [-1, 0] ��Χ�ڵ�б��
    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }

    for (int x = x1; x <= x2; x++) {
        if (steep) {
            image.set(y, x, color);
        }
        else {
            image.set(x, y, color);
        }

        eps += dy;
        // ������λ���� <<1 ���� *2
        if ((eps << 1) >= dx) {
            y = y + yi;
            eps -= dx;
        }
    }
}
void lineBresenham(int x0, int y0, int x1, int y1, TGAImage& image, const TGAColor& color)
{
    bool steep = false;
    //steep ���͵�,
    // y�仯����x��slope > 1�����������꼴�ɱ任������1��
    //�ȼ��ڹ���y = xֱ�����ԳƱ任����������ʱ�ٽ���ÿ�����ص�x, y���ɱ任���ס�
    
    //���Ծ�������if���任 ����6-��2-��1
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }

    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror2 = std::abs(dy) * 2;
    //float derror = std::abs(dy / float(dx));
    int error2 = 0;
    int y = y0;
    for (int x = x0; x <= x1; x++) {
        if (steep) {
            image.set(y, x, color);
        }
        else {
            image.set(x, y, color);
        }
        error2 += derror2;
        //error2 > dx  == derror2-dx == p0>0
        //error > .5
        if (error2 > dx) {
            y += (y1 > y0 ? 1 : -1);  
            //������жϣ�������+1������-1
            error2 -= dx * 2;
        }
    }
}
void bresenham_line(int x1, int y1, int x2, int y2, TGAImage& image, const TGAColor& color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    //dirction
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    int x = x1;
    int y = y1;
    while (x != x2 || y != y2) {
        image.set(x, y, white);
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}
void bresenham_line2(int x1, int y1, int x2, int y2, TGAImage& image, const TGAColor& color)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int stepX = dx >= 0 ? 1 : -1;
    int stepY = dy >= 0 ? 1 : -1;
    dx = abs(dx);
    dy = abs(dy);

    if (dx > dy) { // |m| < 1
        int p = 2 * dy - dx;
        int y = y1;
        for (int x = x1; x != x2; x += stepX) {
            image.set(x, y,white);
            if (p > 0) {
                y += stepY;
                p -= 2 * dx;
            }
            p += 2 * dy;
        }
    }
    else { // |m| >= 1
        int p = 2 * dx - dy;
        int x = x1;
        for (int y = y1; y != y2; y += stepY) {
            image.set(x, y, white);
            if (p > 0) {
                x += stepX;
                p -= 2 * dy;
            }
            p += 2 * dx;
        }
    }
}
//void rst::rasterizer::draw_line(Eigen::Vector3f begin, Eigen::Vector3f end)
//{
//    auto x1 = begin.x();
//    auto y1 = begin.y();
//    auto x2 = end.x();
//    auto y2 = end.y();
//
//    Eigen::Vector3f line_color = { 255, 255, 255 };
//
//    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
//
//    dx = x2 - x1;
//    dy = y2 - y1;
//    dx1 = fabs(dx);
//    dy1 = fabs(dy);
//    px = 2 * dy1 - dx1;
//    py = 2 * dx1 - dy1;
//
//    if (dy1 <= dx1)
//    {
//        if (dx >= 0)
//        {
//            x = x1;
//            y = y1;
//            xe = x2;
//        }
//        else
//        {
//            x = x2;
//            y = y2;
//            xe = x1;
//        }
//        Eigen::Vector3f point = Eigen::Vector3f(x, y, 1.0f);
//        set_pixel(point, line_color);
//        for (i = 0; x < xe; i++)
//        {
//            x = x + 1;
//            if (px < 0)
//            {
//                px = px + 2 * dy1;
//            }
//            else
//            {
//                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
//                {
//                    y = y + 1;
//                }
//                else
//                {
//                    y = y - 1;
//                }
//                px = px + 2 * (dy1 - dx1);
//            }
//            //            delay(0);
//            Eigen::Vector3f point = Eigen::Vector3f(x, y, 1.0f);
//            set_pixel(point, line_color);
//        }
//    }
//    else
//    {
//        if (dy >= 0)
//        {
//            x = x1;
//            y = y1;
//            ye = y2;
//        }
//        else
//        {
//            x = x2;
//            y = y2;
//            ye = y1;
//        }
//        Eigen::Vector3f point = Eigen::Vector3f(x, y, 1.0f);
//        set_pixel(point, line_color);
//        for (i = 0; y < ye; i++)
//        {
//            y = y + 1;
//            if (py <= 0)
//            {
//                py = py + 2 * dx1;
//            }
//            else
//            {
//                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
//                {
//                    x = x + 1;
//                }
//                else
//                {
//                    x = x - 1;
//                }
//                py = py + 2 * (dx1 - dy1);
//            }
//            //            delay(0);
//            Eigen::Vector3f point = Eigen::Vector3f(x, y, 1.0f);
//            set_pixel(point, line_color);
//        }
//    }
//}


int main(int argc, char** argv) {
    TGAImage image(1000, 1000, TGAImage::RGB);
	//image.set(52, 41, red);
    
    Model model = Model("obj/african_head.obj");

     //ѭ��ģ���������������
    for (int i = 0; i < model.nfaces(); i++) {
        std::vector<int> face = model.face(i);
        // ѭ���������������㣬ÿ����������һ����
        for (int j = 0; j < 3; j++) {
            Vec3f v0 = model.vert(face[j]); //[1.2][2.0][0.1]
            Vec3f v1 = model.vert(face[(j + 1) % 3]);
            // ��Ϊģ�Ϳռ�ȡֵ��Χ�� [-1, 1]^3������Ҫ��ģ������ƽ�Ƶ���Ļ������
            // ���� (point + 1) * width(height) / 2 �Ĳ���ѧ��Ϊ�ӿڱ任��Viewport Transformation��
            int x0 = (v0.x + 1.) * 1000 / 2.;
            int y0 = (v0.y + 1.) * 1000 / 2.;
            int x1 = (v1.x + 1.) * 1000 / 2.;
            int y1 = (v1.y + 1.) * 1000 / 2.;
            // ����
            bresenham_line2(x0, y0, x1, y1, image, white);
        }
    }
     
    vector3 a(1, 2, 3);
    vector3 b(1, 2, 8);
    vector3 c(a);
    std::cout << a.x << a.y << a.z<<endl;
    std::cout << vector3Mag(a) << endl;
    std::cout << distance(a,b) << endl;
    std::cout << crossProduct(a,b).x << endl;
    std::cout << "c.x: "<<c.x << endl;
    //std::cout << "glZeroVector.x:" << glZeroVector.x << endl;
    //std::cout<<a<<
    matrix3 jk(1, 1, 1, 1, 1, 1, 1, 1, 1);
    std::cout << "jk.det " << determinant(jk) << endl;
    identety();
    transpose(jk);
    inverse(jk);

	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}

