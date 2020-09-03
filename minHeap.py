def sift_up(minHeap):     # 最小堆插入新元素到末尾后的上浮操作
    parent = (len(minHeap)-1) // 2
    while parent > 0:
        child = 2 * parent
        if child < len(minHeap) - 1 and minHeap[child+1] < minHeap[child]:
            child += 1
        if minHeap[parent] > minHeap[child]:
            tmp = minHeap[child]
            minHeap[child] = minHeap[parent]
            minHeap[parent] = tmp
            parent = parent // 2
        else:
            break


a = [7, 6, 5, 4, 3, 2, 1]
b = [100]
for k in a:
    b.append(k)
    sift_up(b)
print(b)
