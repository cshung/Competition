package snapshot_array

import (
	"fmt"
	"sort"
)

type Record struct {
	snap int
	val  int
}

type SnapshotArray struct {
	id      int
	records map[int][]Record
}

func Constructor(length int) SnapshotArray {
	return SnapshotArray{0, make(map[int][]Record)}
}

func (this *SnapshotArray) Set(index int, val int) {
	records, recordsFound := this.records[index]
	if !recordsFound {
		records = make([]Record, 0)
	}
	this.records[index] = append(records, Record{this.id, val})
}

func (this *SnapshotArray) Snap() int {
	this.id = this.id + 1
	return this.id - 1
}

func (this *SnapshotArray) Get(index int, snap_id int) int {
	records, recordsFound := this.records[index]
	if !recordsFound {
		return 0
	}
	recordIndex := sort.Search(len(records), func(i int) bool { return records[i].snap > snap_id })
	if recordIndex == 0 {
		return 0
	} else {
		return records[recordIndex-1].val
	}
}

func Main() {
	// ["SnapshotArray","set","snap","set","get"]
	// [[3],[0,5],[],[0,6],[0,0]]
	obj := Constructor(3)
	obj.Set(0, 5)
	fmt.Println(obj.Snap())
	obj.Set(0, 6)
	fmt.Println(obj.Get(0, 0))

}
