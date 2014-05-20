<?
class FanndException extends Exception {}

class fannd {
	private $address;
	private $port;

	const ACTION_TRAIN = 1;
	const ACTION_RUN = 3;

	const REPLY_OK = 1;
	const REPLY_FAIL = 0;

	public function __construct($host = '127.0.0.1', $port = 9100) {
		$this->address = gethostbyname($host);
		$this->port = $port;
	}

	private function exec($action_id, array $query) {
		if(!($socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP))) {
			throw new FanndException("Can't create socket");
		}

		if(!($result = socket_connect($socket, $this->address, $this->port))) {
			throw new FanndException("Can't connect ({$result})".socket_strerror(socket_last_error($socket)));
		}

		foreach($query as $k => $v) {
			$query[$k] = implode(',', $v);
		}
		$in = $action_id.'#'.implode("#", $query)."\n";
		var_dump($in);
		socket_write($socket, $in, strlen($in));

		$reply = '';
		do {
			$out = socket_read($socket, 1024);
			$reply .= $out;
		} while ($out);

		$reply = explode('#', $reply);
		if( ((int)$reply[0]) == self::REPLY_FAIL ) {
			throw new FanndException("Fannd fail: {$reply[1]}");
		}

		return explode(',', $reply[1]);
	}

	public function train($inputs, $outputs) {
		$this->exec(self::ACTION_TRAIN, [$inputs, $outputs]);
		return true;
	}

	public function run($inputs) {
		return $this->exec(self::ACTION_RUN, [$inputs]);
	}
}
