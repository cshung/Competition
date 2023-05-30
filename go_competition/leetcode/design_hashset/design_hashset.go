package design_hashset

import (
	"fmt"
)

type MyHashSet struct {
	masks []int64
}

func Constructor() MyHashSet {
	return MyHashSet{nil}
}

func (this *MyHashSet) Add(key int) {
	i := key / 64
	b := key % 64
	if this.masks == nil {

		this.masks = make([]int64, i+1)
	} else if len(this.masks) < i+1 {
		this.masks = append(this.masks, make([]int64, i+1-len(this.masks))...)
	}
	this.masks[i] |= 1 << b
}

func (this *MyHashSet) Remove(key int) {
	i := key / 64
	b := key % 64
	if this.masks == nil {
		this.masks = make([]int64, i+1)
	} else if len(this.masks) < i+1 {
		this.masks = append(this.masks, make([]int64, i+1-len(this.masks))...)
	}
	this.masks[i] &= ^(1 << b)
}

func (this *MyHashSet) Contains(key int) bool {
	i := key / 64
	b := key % 64
	if this.masks == nil {
		this.masks = make([]int64, i+1)
	} else if len(this.masks) < i+1 {
		this.masks = append(this.masks, make([]int64, i+1-len(this.masks))...)
	}
	return (this.masks[i] & (1 << b)) != 0
}

func Main() {

	obj := Constructor()
	obj.Add(1)                   // set = [1]
	obj.Add(2)                   // set = [1, 2]
	fmt.Println(obj.Contains(1)) // return True
	fmt.Println(obj.Contains(3)) // return False, (not found)
	obj.Add(2)                   // set = [1, 2]
	fmt.Println(obj.Contains(2)) // return True
	obj.Remove(2)                // set = [1]
	fmt.Println(obj.Contains(2)) // return False, (already removed)
}
