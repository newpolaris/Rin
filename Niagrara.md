> Optimize mesh rendering

0:03:00 - triangle 1087474 in 2.3ms result is not fast, because envrionment is RTX 2080
0:08:57 - test present mode immediate, disable V-sync
0:29:21 - in a real vulkan application you need some sort of upload syn management might to use transfer queues
         (http://lifeisforu.tistory.com/404?category=837815 ������ ���� 17��, ���� ������ 1��. ������ �����ϴ� ��� �װ��� ����Ѵٰ� �ߴ�)
0:40:45 - Device Local Memory make 0.31 ms
0:43:42 - Draw 10 times, makes mesh shader 10.41 vs 2.3 ms (stroage buffer or FVF)
0:54:26 - Test optimizeVertexCache with randome suffle
1:02:32 - Test push descriptor with position * 1e-9. 1.9 ms > 1.0 ms. �������ѰͰ� ���Ѱ��� ����� 2�������� ���� optimzal �� ����. 5 ~ 10 billion �� ��� �����̰� 5 ���� ������ �� ����� ������ �� ����.
1:04:20 - N triangle > n/2 vertices (minecraft ������ nx2)
          upto 128 and one is used by gl_primitiveCountNV (so, 127) and makes divided by 3. up to 42 triangles
1:09:12 - 16 KB / meshlet > 64 vertices > 16 * 1024 / 64 > 256 byte per vertex
          128 byte chuck (-4 bytes for count, 1 byte per index (so limited to 256))
          if use 128x3 then (128x3 - 4) index > 126 triangles
          if use 128x2 then (128x2 - 4) index >  84 triangles
          if use 128x1 then (128x1 - 4) index >  41 triangles (ndivia article�� 40�̶� ����; introduction to utrning mehs shader)

1:39:12 - perprimitiveNV
2:10:15 - ACMR ratio (average cache miss ratio)  = # of vertex shader invocation / # of triangles         
          0.5 best case
          0.7 
          2.0 minecraft like



happy_buddha, Nvidia 660m, one commandbuffer with wait-idle

        'basic' 'duplicate remove' 'optimize vertex fetch' 'reduce vertex size'
FVF  :   2.54          1.0                0.84                     0.84
PUSH :   2.67          3.8                1.25                     0.91



Worklist:

* FVF (fixed function vertex fuction)
* Device Local Memory

