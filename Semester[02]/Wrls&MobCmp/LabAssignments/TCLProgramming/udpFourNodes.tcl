#Question : Write a TCL script implementing UDP communication(four nodes)

#Solution :

#1 Create a simulator object
set ns [new Simulator]
#2 Open trace file for event trace 
set nf [open out.tr w]
$ns trace-all $nf
#3 Open NAM file for visualizing event
set f [open out.nam w]
$ns namtrace-all $f
#4 Create four nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
#5 Create duplex-links 
$ns duplex-link $n0 $n1 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail
$ns duplex-link $n2 $n3 1Mb 10ms DropTail
$ns duplex-link $n3 $n1 10Mb 10ms DropTail
$ns duplex-link $n0 $n2 10Mb 10ms DropTail
#6 Create and attach UDP agent at n0
set udp [new Agent/UDP]
$ns attach-agent $n0 $udp
#7 Create and attach null agent at n3
set null [new Agent/Null]
$ns attach-agent $n3 $null
#8 Create and attach CBR(cost and bit rate) traffic with udp
set cbr [new Application/Traffic/CBR]
$cbr set packetSize_ 500
$cbr set interval_ 0.005
$cbr attach-agent $udp
#9 Connect agents
$ns connect $udp $null
#10 Define finish process
proc finish {} {
	global ns nf f
	$ns flush-trace
	close $nf
	close $f
	exec nam out.nam &
	exit 0
	}
#11 Schedule events for CBR
$ns at 0.5 "$cbr start"
$ns at 3.0  "$cbr stop"
#12 Call the finish procedure after 5 seconds of simulation time
$ns at 5.00  "finish"
#13 Run the simulation
$ns run
