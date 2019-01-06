```
rval = buildgraph(&G, ncount, ecount, elist, &D);
```

```
rval = build_distobj(&D, ncount, dat); 
```

这个没有问题，因为后面我们只用到了 `D->dat`

而 `ncount`, `ecount` 还有 `elist` 都是传进来的。

其中 `ncount` 是根据原始文件读取内容得来的。

而 `ecount` 和 `elist` 是通过下面这个函数计算得来的。

```
CCkdtree_quadrant_k_nearest (&localkt, ncount, quadtry,
                           &dat, (double *) NULL, 1, &tempcount, &templist,
                           run_silently, &rstate)
```

确定一下 elist 是不是按照边的顺序存储的。

这个和我们要算的东西没有关系，这个只是一个 goodlist，或者说 candidates.