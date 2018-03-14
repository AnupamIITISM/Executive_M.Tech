#Question : Write a TCL script implementing ring topology using UDP protocol

#Solution :

#1 Create a simulator object
set ns [new Simulator]
#2 Tell the simulator to use dynamic routing
$ns rtproto DV
#3 Open the nam trace file
set nf [open out.nam w]
$ns namtrace-all $nf
#4 Define a 'finish' procedure
proc finish {} {
	global ns nf
    $ns flush-trace
	close $nf
	exec nam out.nam &
	exit 0
}
#5 Create seven nodes
for {set i 0} {$i < 7} {incr i} {
set n($i) [$ns node]
}
#6 Create duplex-links between the nodes
for {set i 0} {$i < 7} {incr i} {
        $ns duplex-link $n($i) $n([expr ($i+1)%7]) 1Mb 10ms DropTail
}
#7 Create a UDP agent and attach it to node n(0)
set udp0 [new Agent/UDP]
$ns attach-agent $n(0) $udp0
#8 Create a CBR traffic source and attach it to udp0
set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.005
$cbr0 attach-agent $udp0
#9 Create a Null agent (a traffic sink) and attach it to node n(3)
set null0 [new Agent/Null]
$ns attach-agent $n(3) $null0
#10 Connect the traffic source with the traffic sink
$ns connect $udp0 $null0  
#11 Schedule events for the CBR agent and the network dynamics
$ns at 0.5 "$cbr0 start"
$ns rtmodel-at 1.0 down $n(1) $n(2)
$ns rtmodel-at 2.0 up $n(1) $n(2)
$ns at 4.5 "$cbr0 stop"
#12 Call the finish procedure after 5 seconds of simulation time
$ns at 5.0 "finish"
#13 Run the simulation
$ns run