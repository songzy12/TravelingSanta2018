r-opt move: 

* Let T be the current tour. At each iteration step the algorithm attempts to find two sets of links, X = {x1, ..., xr} and Y = {y1, ..., yr}, such that, if the links of X are deleted from T and replaced by the links of Y, the result is a better tour. This interchange of links is called a r-opt move .



主文件：`lk_main.c`，

## lk_main.c

```
int main (int ac, char **av)
```

读取参数的函数：`parseargs `

```
        case 't':
            time_bound = atof (boptarg);
            break;
```

搜索 `time_bound`, 找到 `CClinkern_tour `

这个函数在 `linkern.c`，

## linkern.c

```
/*    EXPORTED FUNCTIONS:                                                   */
/*                                                                          */
/*  int CClinkern_tour (int ncount, CCdatagroup *dat, int ecount,           */
/*      int *elist, int stallcount, int repeatcount, int *incycle,          */
/*      int *outcycle, double *val                                          */
/*      int silent, double time_bound, double length_bound,                 */
/*      char *saveit_name, int kicktype, CCrandstate *rstate)               */
/*    RUNS Chained Lin-Kernighan.                                           */
/*    -ncount (the number of nodes int the graph)                           */
/*    -dat (coordinate dat)                                                 */
/*    -ecount (the number of good edges - should not be 0)                  */
/*    -elist (the good edges in end1 end2 format)                           */
/*    -stallcount (the max number of 4-swaps without progress               */
/*    -repeatcount (the number of 4-swap kicks)                             */
/*    -incycle (a starting cycle, in node node node format - can be NULL)   */
/*    -outcycle (returns the cycle - can be NULL)                           */
/*    -run_slightly (if nonzero, then very little info will be printed)     */
/*    -time_bound (if postive, then the search will stop after the kick     */
/*       that puts the running time above this number of seconds)           */
/*    -length_bound (if postive, then the search will stop after the kick   */
/*       that puts the tour at or below this length)                        */
/*    -saveit_name (if non NULL then the tour will be saved to this file    */
/*       after every 10000 kicks - if it has improved)                      */
/*    -kicktype (specifies the type of kick used - should be one of         */
/*       CC_LK_RANDOM_KICK, CC_LK_GEOMETRIC_KICK, CC_LK_CLOSE_KICK, or      */
/*       CC_LK_WALK_KICK)                                                   */
/*                                                                          */
/*    NOTES: If incycle is NULL, then a random starting cycle is used. If   */
/*     outcycle is not NULL, then it should point to an array of length     */
/*     at least ncount.                                                     */
```



`CClinkern_tour ` 最主要的就是下面这两句：

1. 用于计算路径长度：

```
*val = cycle_length (ncount, tcyc, &D);
```
2. 在一些初始化准备工作之后：

```
rval = repeated_lin_kernighan (&G, &D, tcyc, stallcount, repeatcount,
                 val, time_bound, length_bound, saveit_name, silent,
                 kicktype, &intptr_world, &edgelook_world, rstate);
```

对于我们这个题目来说，首先 cycle_length 的计算方式不同。

在 `repeated_lin_kernighan` 里，大概有三个函数需要知道在做什么：

```
		if (IMPROVE_SWITCH == -1 || round < IMPROVE_SWITCH) {
            rval = random_four_swap (G, D, &Q, &F, &kdt, &delta, kicktype,
                                     &winstack, &fstack, intptr_world, rstate);
            if (rval) {
                fprintf (stderr, "random_four_swap failed\n"); goto CLEANUP;
            }
        } else {
            delta = kick_improve (G, D, &E, &Q, &F, &winstack, &fstack, intptr_world);
        }
        
        fstack.counter = 0;
        t = best + delta;
        lin_kernighan (G, D, &E, &Q, &F, &t, win_cycle, &winstack, &fstack,
                       intptr_world, edgelook_world);
```

* `random_four_swap`
* `kick_improve`
* `lin_kernighan`

在 `lin_kernighan` 里，有一个 `improve_tour ` 的函数

```
		delta = improve_tour (G, D, E, Q, F, start, fstack, intptr_world,
                              edgelook_world);
```

在 `improve_tour` 里，有一个  `Edgelen` 的函数：

```
gain = Edgelen (t1, t2, D);
```

```
#define Edgelen(n1, n2, D)  dist (n1, n2, D)
```

在 `dist` 里：

```
        D->cacheval[ind] = CCutil_dat_edgelen (i, j, D->dat);
```

## edgelen.c

在 `CCutil_dat_edgelen ` 里，

```
    return (dat->edgelen)(i, j, dat);
```

而 `data->edgelen` 是由`CCutil_dat_setnorm` 决定的：

```
int CCutil_dat_setnorm (CCdatagroup *dat, int norm)
```

让我们回到最早的时候在 `linkern` 里提到的那个 `cycle_length` 的函数：

```
	for (i = 1; i < ncount; i++) {
        val += (double) Edgelen (cyc[i - 1], cyc[i], D);
    }
```

而这个参数在 `lk_main` 最开始的时候是通过 N 来传入的。

```
		case 'N':
            inorm = atoi(boptarg);
            switch (inorm) {
            case 0: norm = CC_MAXNORM; break;
            case 1: norm = CC_MANNORM; break;
            case 2: norm = CC_EUCLIDEAN; break;
            case 3: norm = CC_EUCLIDEAN_3D; break;
            case 4: norm = CC_USER; break;
            case 5: norm = CC_ATT; break;
            case 6: norm = CC_GEOGRAPHIC; break;
            case 7: norm = CC_MATRIXNORM; break;
            case 8: norm = CC_DSJRANDNORM; break;
            case 9: norm = CC_CRYSTAL; break;
            case 10: norm = CC_SPARSE; break;
            case 11: norm = CC_RHMAP1; break;
            case 12: norm = CC_RHMAP2; break;
            case 13: norm = CC_RHMAP3; break;
            case 14: norm = CC_RHMAP4; break;
            case 15: norm = CC_RHMAP5; break;
            case 16: norm = CC_EUCTOROIDAL; break;
            case 17: norm = CC_GEOM; break;
            case 18: norm = CC_EUCLIDEAN_CEIL; break;
            default:
                usage (av[0]);
                return 1;
            }
```



很好，现在的事情就变成了：如何在 `edgelen.c` 里实现一个新的 norm 函数？