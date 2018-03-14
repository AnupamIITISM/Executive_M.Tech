#Question : Write a TCL script implementing star topology using UDP protocol

#Solution :

#1 Create a simulator object
set ns [new Simulator]
$ns color 1 Red
$ns color 2 Blue
#2 Open trace file for event trace
set f [open out.tr w]
$ns trace-all $f
#3 Open NAM file for visualizing event
set nf [open out.nam w]
$ns namtrace-all $nf
#4 Create four nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
#5 Create duplex-links 
$ns duplex-link $n0 $n2 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail
$ns duplex-link $n2 $n3 1Mb 10ms SFQ

$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link-op $n1 $n2 orient right-up
$ns duplex-link-op $n2 $n3 orient right
#6 Create and attach UDP agent at n0
set udp0 [new Agent/UDP]
$udp0 set class_ 1
$ns attach-agent $n0 $udp0
#7 Create and attach CBR(cost and bit rate) traffic with udp0
set cbr [new Application/Traffic/CBR]
$cbr set packetSize_ 500
$cbr set interval_ 0.005
$cbr attach-agent $udp0
#8 Create and attach UDP agent at n1
set udp1 [new Agent/UDP]
$udp1 set class_ 2
$ns attach-agent $n1 $udp1
#9 Create and attach CBR(cost and bit rate) traffic with udp1
set cbr1 [new Application/Traffic/CBR]
$cbr1 set packetSize_ 500
$cbr1 set interval_ 0.005
$cbr1 attach-agent $udp1
#10 Create and attach UDP agent at n2
set udp2 [new Agent/UDP]
$ns attach-agent $n2 $udp2
#11 Create and attach CBR(cost and bit rate) traffic with udp2
set cbr2 [new Application/Traffic/CBR]
$cbr2 set packetSize_ 500
$cbr2 set interval_ 0.005
$cbr2 attach-agent $udp2
#12 Create and attach null agent at n3
set null0 [new Agent/Null]
$ns attach-agent $n3 $null0
#13 Connect agents
$ns connect $udp0 $null0
$ns connect $udp1 $null0
$ns connect $udp2 $null0
#14 Define finish process
proc finish {} {
	global ns nf f
	$ns flush-trace
	close $nf
	close $f
	exec nam out.nam &
	exit 0
}
#15 Schedule events for CBRs
$ns at 0.5 "$cbr start"
$ns at 3.0 "$cbr stop"
$ns at 0.5 "$cbr1 start"
$ns at 3.0 "$cbr1 stop"
$ns at 0.5 "$cbr2 start"
$ns at 3.0 "$cbr2 stop"
#16 Call the finish procedure after 5 seconds of simulation time
$ns at 5.0 "finish"
#17 Run the simulation
$ns run