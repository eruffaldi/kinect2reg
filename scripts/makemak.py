p = [0.0885576,0.610703,1.6797,0.126741,0.274673,1.39562,0.0885825,0.0671344,1.65925,0.152189,-0.112166,1.58045,0.0887249,-0.005202,1.75204,0.000612795,-0.0263006,1.72793,0.0589881,-0.137325,1.53402,-0.295456,0.591488,1.68194,-0.374953,0.286578,1.40035,-0.309928,0.0436248,1.6643,-0.288757,-0.151013,1.53413,-0.297834,-0.0174438,1.75956,-0.214367,-0.0311574,1.71948,-0.382342,-0.129365,1.56724]

k = 4; # points per side
dx = 0.01; # cubesize

o = open("out.ply","w")
o.write("""ply
format ascii 1.0
element vertex %d
property float x
property float y
property float z
property uchar red
property uchar green
property uchar blue
end_header
""" % (len(p)/3*k*k*k))

prep = []
dxk = dx/k
for ix in range(0,k):
	for iy in range(0,k):
		for iz in range(0,k):
			prep.append((dxk*ix,dxk*iy,dxk*iz))

de = dx/2;
for i in range(0,len(p),3):
	v = p[i:i+3]
	print v
	for w in prep:
		out = ((w[0]+v[0]-de)*1000,(w[1]+v[1]-de)*1000,(w[2]+v[2]-de)*1000)
		o.write("%f %f %f 0 255 0\n" % out)

