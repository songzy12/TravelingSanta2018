这个函数需要大改：

```
static double improve_tour(graph *G, distobj *D, adddel *E, aqueue *Q,
                           CClk_flipper *F, int t1, flipstack *fstack,
                           CCptrworld *intptr_world, CCptrworld *edgelook_world)
{
    CClk_childnode* t2 = CClinkern_flipper_next(F, t1);
    int gain, Gstar = 0;

    gain = Edgelen(t1, t2, D);
    markedge_del(t1, t2, E);

    if (step(G, D, E, Q, F, 0, gain, &Gstar, t1, t2, fstack, intptr_world, edgelook_world) == 0)
    {
        Gstar = weird_second_step(G, D, E, Q, F, gain, t1, t2, fstack,
                                  intptr_world, edgelook_world);
    }
    unmarkedge_del(t1, t2, E);

    if (Gstar)
    {
        MARK(t1, Q, F, D, G, intptr_world);
        MARK(t2, Q, F, D, G, intptr_world);
    }
    return (double)Gstar;
}
```

首先是 `t1` 的来源。

```
start = pop_from_active_queue(Q, intptr_world); 
```

这个就要看一下 Q 的初始化：

```
		for (i = 0; i < ncount; i++)
        {
            add_to_active_queue(tcyc[i], &Q, intptr_world);
        }
```

是从这里开始丢失位置信息的。