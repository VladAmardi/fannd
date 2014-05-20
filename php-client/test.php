<?
require_once "./fannd.inc.php";
$ann = new fannd('127.0.0.1', 9100);

for($i = 0; $i < 1000; $i++)
//var_dump( $ann->run([1,1,1]) );
$ann->train([1,1], [1]);
