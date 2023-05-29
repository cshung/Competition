package design_parking_system

import (
	"fmt"
)

type ParkingSystem struct {
	available []int
}

func Constructor(big int, medium int, small int) ParkingSystem {
	return ParkingSystem{[]int{big, medium, small}}
}

func (this *ParkingSystem) AddCar(carType int) bool {
	if this.available[carType-1] > 0 {
		this.available[carType-1]--
		return true
	} else {
		return false
	}
}

func Main() {
	obj := Constructor(1, 1, 0)
	fmt.Println(obj.AddCar(1))
	fmt.Println(obj.AddCar(2))
	fmt.Println(obj.AddCar(3))
	fmt.Println(obj.AddCar(1))
}
