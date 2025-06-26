         w[i][j]=w[i][j-1]+q[i]+p[i];
         int k=Find(i,j);
        c[i][j]=w[i][j]+c[i][k-1]+c[k][j];
        r[i][j]=k;