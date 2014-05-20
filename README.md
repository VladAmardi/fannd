FANND
=====

Build on C++ FANN server and PHP client.

##Server:
./fannd --help<br />
-h,--help - show help<br />
-v,--verbose - enable verbose mode<br />
-o,--open path<br />
-c,--create path,num_layers,num_input,num_neurons_hidden,num_output<br />
<br />
For example, you can create ANN for XOR:<br />
./fannd -c /tmp/fann,3,2,3,1<br />
<br />
And run it:<br />
./fannd -o /tmp/fann<br />
<br />
You can configure host and port of server in automatically created .ini file /tmp/fann/config.ini:
[Server]<br />
Host = 127.0.0.1<br />
Port = 9100<br />

##PHP Client:
require_once "./fannd.inc.php";<br />
$ann = new fannd('127.0.0.1', 9100);<br />
$ann->train(array $inputs, array $outputs);<br />
$ann->run(array $inputs);<br />
<br />

