/**
 * Author: Simon Lindholm
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: Segment tree with ability to add or set values of large intervals, and compute max of intervals.
 * Can be changed to other things.
 * Use with a bump allocator for better performance, and SmallPtr or implicit indices to save memory.
 * Time: O(\log N).
 * Usage: Node* tr = new Node(v, 0, sz(v));
 * Status: stress-tested a bit
 */
#pragma once

#include "../various/BumpAllocator.h"

struct STLazy {
    int n;
    vector<int> tr, lz;

    STLazy(int n) : n(n), tr(4 * n + 8), lz(4 * n + 8) {}

    void push(int v, int lo, int hi) {
        if (lz[v] != 0) {
            tr[v] += lz[v];
            if (lo + 1 != hi) {
                lz[v * 2] += lz[v];
                lz[v * 2 + 1] += lz[v];
            }
            lz[v] = 0;
        }
    }

    void update(int v, int lo, int hi, int l, int r, int val) {
        push(v, lo, hi);
        if (lo >= hi || lo >= r || hi <= l)
            return;
        if (lo >= l && hi <= r) {
            lz[v] += val;  // put lazy tag here
            push(v, lo, hi);
            return;
        }
        int mid = (lo + hi) / 2;
        update(v * 2, lo, mid, l, r, val);
        update(v * 2 + 1, mid, hi, l, r, val);
        tr[v] = max(tr[v * 2], tr[v * 2 + 1]);
    }

    int query(int v, int lo, int hi, int l, int r) {
        push(v, lo, hi);
        if (lo >= hi || lo >= r || hi <= l)
            return -INF; 
        if (lo >= l && hi <= r)
            return tr[v];
        int mid = (lo + hi) / 2;
        int p1 = query(v * 2, lo, mid, l, r);
        int p2 = query(v * 2 + 1, mid, hi, l, r);
        return max(p1, p2);
    }

    void update(int l, int r, int val) {
        update(1, 0, n, l, r, val);
    }

    int query(int l, int r) {
        return query(1, 0, n, l, r);
    }
};
