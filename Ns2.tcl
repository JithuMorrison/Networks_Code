set ns [new Simulator]

$ns color 1 Blue 
$ns color 2 Red

set nf [open out.nam w]      
$ns namtrace-all $nf

set tf [open cong.xg w]

proc finish {} {
    global ns nf tf
    $ns flush-trace
    close $nf
    close $tf
    exec nam out.nam &
    exec xgraph cong.xg &  # works only if Xgraph available
    exit 0
}

proc throughput {time} {
    global ns nf tcp
    set packets [$tcp set packetSize_]
    set thru [expr ($packets * 8)/($time/1.0e6)]
    puts $tf "$time $thru"
    if { $time < 5.0 } {
        $ns at [expr ($time + 0.3)] "throughput [expr ($time + 0.3)]"
    }
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

$ns duplex-link $n0 $n1 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail

$ns duplex-link-op $n0 $n1 orient right
$ns duplex-link-op $n1 $n2 orient right

set tcp [new Agent/TCP]
$ns attach-agent $n0 $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n1 $sink
$ns connect $tcp $sink
$tcp set class_ 1 # 1 - Tahoe, 2 - Reno, 3 - New Reno
$tcp set fid_ 2

set udp [new Agent/UDP]
$ns attach-agent $n2 $udp
set null [new Agent/Null]
$ns attach-agent $n1 $null
$ns connect $udp $null
$udp set fid_ 1

$ns queue-limit $n0 $n1 10
$ns duplex-link-op $n0 $n1 queuePos 0.5

set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set packetSize_ 1000
$ftp set interval 0.1
$ftp set rate_ 1Mb
$ftp set random_ false

set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp 
$cbr set packetSize_ 1000
$cbr set interval 0.1
$cbr set rate_ 1Mb
$cbr set random_ false

$ns rtproto DV # DV - Distance vector protocol, LS - Link state protocol
$ns rtmodel 0.5 down $n0 $n1
$ns rtmodel 1.5 up $n0 $n1

$ns at 0.1 "throughput 0.1"
$ns at 0.5 "$cbr start"
$ns at 0.6 "$ftp start"
$ns at 4.4 "$ftp stop"
$ns at 4.5 "$cbr stop"
$ns at 5.0 "finish"

puts "CBR packet size = [$cbr set packetSize_]"
puts "CBR interval = [$cbr set interval_]"

$ns run
