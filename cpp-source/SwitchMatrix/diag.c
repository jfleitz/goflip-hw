
	/*
	bool_t DebounceSwitch2()
{
    static uint16_t State = 0; // Current debounce status
    State=(State<<1) | !RawKeyPressed() | 0xe000;
    if(State==0xf000)return TRUE;
    return FALSE; 
}
*/
BOOL RawUpSwitch(){
	char temp;
	temp = PCIN;
	return ((temp & 0x08) == 0x00);
}

BOOL DebounceUpSwitch(){
	static UINT16 upState = 0; //current debounce status
	upState=(upState<<1) | !RawUpSwitch() | 0xe000;
	if(upState==0xf000) return TRUE;
	return FALSE;
}

void DiagISR()
{
	
	if(DebounceUpSwitch()){
		//pressed, so increment where we are in the diagnosis
		if(_diagMode>4)
			_diagMode = 0;
		else
			_diagMode++;
		
		switch(_diagMode){
			case 1:
				//Report any switches that are down
				break;
			case 2:
				//Report on Leading Edge
				break;
			case 3:
				//Report on falling edge
				break;
			default:
				//nothing
			}
	}
}
	
	

//Dont think we need, but maybe keep for diag usage
void blinkISR(){
	if(_timerControl>3){
		_timerControl = 0;
	}
	
	switch(_timerControl){
		case 0:
			_slowBlink=0x00;
			_fastBlink =0x00;
			break;
		case 1:
			_slowBlink = 0x00;
			_fastBlink=0x01;
			break;
		case 2:
			_slowBlink = 0x01;
			_fastBlink = 0x00;
			break;
		case 3:
			_slowBlink = 0x01;
			_fastBlink = 0x01;
			break;
		}
		
		_timerControl++;
	}
}
