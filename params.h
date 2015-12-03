
void fillin(Freenect2Device::IrCameraParams &depth_p, Freenect2Device::ColorCameraParams &rgb_p)
{

	// from text file
	float depth_cx = 253.9832;
    float depth_cy = 211.093994;
    float depth_depth_q = 0.00999999978;
    float depth_fx = 365.150208;
    float depth_fy = 365.150208;
    float depth_k1 = 0.0922871977;
    float depth_k2 = -0.266797304;
    float depth_k3 = 0.0901915208;



    float color_color_q = 0.00219899998;
    float color_cx = 959.5;
    float color_cy = 539.5;
    float color_fx = 1081.37207;
    float color_fy = 1081.37207;
    float color_mx_x0y0 = 0.152766302;
    float color_mx_x0y1 = 0.00462980801;
    float color_mx_x0y2 = -8.62425368e-05;
    float color_mx_x0y3 = 2.66473307e-05;
    float color_mx_x1y0 =0.640707493;
    float color_mx_x1y1 = 0.000260630302;
    float color_mx_x1y2 = 0.000386019994;
    float color_mx_x2y0 = -8.80247826e-05;
    float color_mx_x2y1 = 7.26420622e-05;
    float color_mx_x3y0 = 0.000523260387;
    float color_my_x0y0 = 0.035591729;
    float color_my_x0y1 = 0.640462875;
    float color_my_x0y2 = 0.000211564999;
    float color_my_x0y3 = 0.000705449376;
    float color_my_x1y0 = -0.00469533494;
    float color_my_x1y1 = 6.66987689e-05;
    float color_my_x1y2 = 3.74624688e-05;
    float color_my_x2y0 = -9.42075494e-05;
    float color_my_x2y1 = 0.000468305807;
    float color_my_x3y0 = 1.641368e-05;
    float color_shift_m = 52;
    float color_shift_d = 863;

    depth_p.fx = depth_fx;
depth_p.fy = depth_fy;
depth_p.cx = depth_cx;
depth_p.cy = depth_cy;
depth_p.k1 = depth_k1;
depth_p.k2 = depth_k2;
depth_p.k3 = depth_k3;
depth_p.p1 = 0;
depth_p.p2 = 0;
rgb_p.fx = color_fx;
rgb_p.fy = color_fy;
rgb_p.cx = color_cx;
rgb_p.cy = color_cy;
rgb_p.shift_d = color_shift_d;
rgb_p.shift_m = color_shift_m;
rgb_p.mx_x3y0 = color_mx_x3y0;
rgb_p.mx_x0y3 = color_mx_x0y3;
rgb_p.mx_x2y1 = color_mx_x2y1;
rgb_p.mx_x1y2 = color_mx_x1y2;
rgb_p.mx_x2y0 = color_mx_x2y0;
rgb_p.mx_x0y2 = color_mx_x0y2;
rgb_p.mx_x1y1 = color_mx_x1y1;
rgb_p.mx_x1y0 = color_mx_x1y0;
rgb_p.mx_x0y1 = color_mx_x0y1;
rgb_p.mx_x0y0 = color_mx_x0y0;
rgb_p.my_x3y0 = color_my_x3y0;
rgb_p.my_x0y3 = color_my_x0y3;
rgb_p.my_x2y1 = color_my_x2y1;
rgb_p.my_x1y2 = color_my_x1y2;
rgb_p.my_x2y0 = color_my_x2y0;
rgb_p.my_x0y2 = color_my_x0y2;
rgb_p.my_x1y1 = color_my_x1y1;
rgb_p.my_x1y0 = color_my_x1y0;
rgb_p.my_x0y1 = color_my_x0y1;
rgb_p.my_x0y0 = color_my_x0y0;

}