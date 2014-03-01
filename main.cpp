#include <cstdio>
#include <cstdlib>
#include <iostream>
#define ABS(x) (x<0?-x:x)

using namespace std;

int map[3][3];
int gh[3][3];

int check()
{
	for( int i = 0 ; i < 3 ; ++i )
	{
		if( map[i][0] == map[i][1] && map[i][1] == map[i][2] && map[i][0] != 0 )
			return map[i][0];
		if( map[0][i] == map[1][i] && map[1][i] == map[2][i] && map[0][i] != 0 )
			return map[0][i];
	} 

	if( map[0][0] == map[1][1] && map[1][1] == map[2][2] && map[0][0] != 0 )
		return map[0][0];

	if( map[2][0] == map[1][1] && map[1][1] == map[0][2] && map[0][0] != 0 )
		return map[2][0];

	return 0;
}

int dfs( int m , int n , int k )
{
	bool t = false;
	for( int i = 0 ; i < 3 ; ++i )
		for( int j = 0 ; j < 3 ; ++j )
		{
			if( map[i][j] == 0 )
				t = true;
		}
	
	int r = check();
	if( r != 0 )
		gh[m][n] += r*100;
	if( t == false )
		return 0;
		


	if( t == true )
	for( int i = 0 ; i < 3 ; ++i )
		for( int j = 0 ; j < 3 ; ++j )
		{
			if( map[i][j] == 0 )
			{
				map[i][j] = k;
				int z = dfs( m,n, k == 5 ? -5 : 5 );	
				map[i][j] = 0;
				if( z != 0 )	
				{
					return z;
				}
			}
		}
}

int printM()
{
			cout << "=========MAP==========" << endl;
			for( int i = 0 ; i<3 ; ++i )
			{
				for( int j = 0 ; j<3 ; ++j )
				{
                    if( map[i][j]==0)
                        putchar('|');
                    else
                        putchar(' ');
					if( map[i][j] == 5 )
						cout << "O";
					else if( map[i][j] == -5 )
						cout << "X";
					else 
						cout << char('0'+i*3+j);
                    if( map[i][j]==0)
                        putchar('|');
                    else
                        putchar(' ');
				}
				cout << "\n---------" << endl;
			}
			cout << "=====================" << endl;
}

int reset(int k)
{
        
        for( int i = 0 ; i<3 ; ++i )
        {
            for( int j = 0 ; j<3 ; ++j )
            {
                gh[i][j] = 0;
            }
        }
        
        if( k==1 )
        for( int i = 0 ; i<3 ; ++i )
        {
            for( int j = 0 ; j<3 ; ++j )
            {
                map[i][j] = 0;
            }
        }
}

int main()
{
RESTART:
     reset(1);
 	 int m=1,n=1,choo;
     puts("new game START\nyou got O side , com got X side\n   1.first player\n   2.second player\nChoose [1/2]");
     scanf(" %d",&choo);
     if( choo==2 )
     {
        int a=rand()%9;
        map[a/3][a%3] = -5; 
     }
     else if( choo!=1 )
     {
        goto RESTART;
     }
     
        
		    printM();	
	 while( puts("your turn\n choose number |x| or 33 to restart new game") && scanf(" %d",&m )!=EOF ) 
     {
           if( m==33 )
              goto RESTART;
           if( !(0<=m&&m<=9&&map[m/3][m%3]==0) )
           {
               puts("error value");
               continue;
           }

	        reset(2);	
			map[m/3][m%3] = 5;
		    printM();	
			//puts("calc");
			for( int i = 0 ; i<3 ; ++i )
				for( int j = 0 ; j<3 ; ++j )
					if( map[i][j] == 0 )
					{
						map[i][j] = -5;
						int ch = check();
						map[i][j] = 0;
						if( ch != 0 )
						{
							gh[i][j] += 1000000;
						}
						map[i][j] = 5;
						int zf = check();
						map[i][j] = 0;
						if( zf != 0 )
						{
							gh[i][j] += 10000;
						}
						else if( ch == 0 )
						{
								map[i][j] = -5;
								dfs( i , j , -5 );
								map[i][j] = 0;

								map[i][j] = 5;
								dfs( i , j , 5 );
								map[i][j] = 0;
						}
					}

			int maxx , maxy , maxv = 0;
			for( int i = 0 ; i < 3 ; ++i )
				for( int j = 0 ; j < 3 ; ++j )
				{
					//cout << i << " " << j << "  " << gh[i][j] << endl;
					if( maxv < ABS(gh[i][j]) )
					{
						maxv = ABS(gh[i][j]);
						maxx=i;
						maxy=j;
					}
				}
	
			
			map[maxx][maxy] = -5;
			
		    printM();	
			if( check() != 0 )
			{
				puts("GAME OVER");
                goto RESTART;
			}

            bool chk=false;
            for( int i = 0 ; i<3 ; ++i )
                for( int j = 0 ; j<3 ; ++j )
                    if( map[i][j] == 0 )
                        chk = true;
            if(!chk)
                goto RESTART;
	}
}

