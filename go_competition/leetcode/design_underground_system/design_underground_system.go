package design_underground_system

import (
	"fmt"
)

type StationInfo struct {
	name  string
	time  int
	count int
}

type CheckInInfo struct {
	station string
	time    int
}

type UndergroundSystem struct {
	checkIns    map[int]CheckInInfo
	travelTimes map[string]StationInfo
}

func Constructor() UndergroundSystem {
	return UndergroundSystem{
		checkIns:    make(map[int]CheckInInfo),
		travelTimes: make(map[string]StationInfo),
	}
}

func (this *UndergroundSystem) CheckIn(id int, stationName string, t int) {
	this.checkIns[id] = CheckInInfo{stationName, t}
}

func (this *UndergroundSystem) CheckOut(id int, stationName string, t int) {
	checkIn := this.checkIns[id]
	travelTime := t - checkIn.time
	key := checkIn.station + "->" + stationName
	if info, ok := this.travelTimes[key]; ok {
		info.time += travelTime
		info.count++
		this.travelTimes[key] = info
	} else {
		this.travelTimes[key] = StationInfo{stationName, travelTime, 1}
	}
	delete(this.checkIns, id)
}

func (this *UndergroundSystem) GetAverageTime(startStation string, endStation string) float64 {
	key := startStation + "->" + endStation
	info := this.travelTimes[key]
	return float64(info.time) / float64(info.count)
}

func Main() {
	undergroundSystem := Constructor()
	undergroundSystem.CheckIn(45, "Leyton", 3)
	undergroundSystem.CheckIn(32, "Paradise", 8)
	undergroundSystem.CheckIn(27, "Leyton", 10)
	undergroundSystem.CheckOut(45, "Waterloo", 15)
	undergroundSystem.CheckOut(27, "Waterloo", 20)
	undergroundSystem.CheckOut(32, "Cambridge", 22)
	fmt.Println(undergroundSystem.GetAverageTime("Paradise", "Cambridge"))
	fmt.Println(undergroundSystem.GetAverageTime("Leyton", "Waterloo"))
	undergroundSystem.CheckIn(10, "Leyton", 24)
	fmt.Println(undergroundSystem.GetAverageTime("Leyton", "Waterloo"))
	undergroundSystem.CheckOut(10, "Waterloo", 38)
	fmt.Println(undergroundSystem.GetAverageTime("Leyton", "Waterloo"))
}
