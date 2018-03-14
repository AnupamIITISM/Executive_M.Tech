#Question : Write a TCL script for connecting two nodes using TCP protocol

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
$ns duplex-link $n0 $n1 10Mb 10ms DropTail
$ns duplex-link $n1 $n2 10Mb 10ms DropTail
$ns duplex-link $n2 $n3 10Mb 10ms DropTail
$ns duplex-link $n3 $n1 10Mb 10ms DropTail
$ns duplex-link $n0 $n2 10Mb 10ms DropTail
#6 Create and attach TCP sender agent at n0
set tcp [new Agent/TCP]
$ns attach-agent $n0 $tcp
#7 Create and attach TCP receiver agent at n3
set sink [new Agent/TCP]
$ns attach-agent $n3 $sink
#8 Create and attach CBR(cost and bit rate) traffic with tcp
set cbr [new Application/Traffic/CBR]
$cbr set packetSize_ 500
$cbr set interval_ 0.005
$cbr attach-agent $tcp
#9 Connect agents
$ns connect $tcp $sink
#10 Define finish process
proc finish {} {	 
	global ns nf f
	$ns flush-trace
	close $nf
	close $f
	exec nam out.nam &
	exit 0
}
#11 Schedule events for CBRs
$ns at 0.5 "$cbr start"
$ns at 3.0  "$cbr stop"
#12 Call the finish procedure after 5 seconds of simulation time
$ns at 5.00  "finish"
#13 Run the simulation
$ns run