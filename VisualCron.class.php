<?php
/*
Visual Cron Job
2015 Joseph Orlando
*/

set_time_limit(300);
class VisualCron {
	public static $Crontab = array();
	public static function AddCron($CronFormat){
		$CronExp = explode(' ', $CronFormat);
		if(count($CronExp) > 6){
			for($i = 6; $i <= (count($CronExp)-1); $i++){
				$CronExp[5] .= ' '.$CronExp[$i];
				unset($CronExp[$i]);
			}
		}
		if(count($CronExp) == 6){
			self::$Crontab[] = array('minute'=>$CronExp[0], 'hour'=>$CronExp[1], 'dom'=>$CronExp[2], 'moy'=>$CronExp[3], 'dow'=>$CronExp[4], 'command'=>$CronExp[5]);
		}else{
			self::$Crontab[] = array('minute'=>$CronExp[0], 'hour'=>$CronExp[1], 'dom'=>$CronExp[2], 'moy'=>$CronExp[3], 'dow'=>$CronExp[4], 'command'=>'<no command given>');
		}
	}
	public static function ViewCron(){
		$CurrentTime = strtotime(date('m/01/Y').' 12:00AM');
		$EndTime = strtotime('+1 month', strtotime(date('m/j/Y').' 12:00AM'));
		$Output = array();
		
		// Iterate through every minute in the month
		while($CurrentTime <= $EndTime){
			// Iterate through every given cron job
			foreach(self::$Crontab as $i=>$CronJob){
				// Check if Day of the Week matches
				if((int)$CronJob['dow'] != (int)date('w', $CurrentTime) && $CronJob['dow'] != '*'){
					if(strpos($CronJob['dow'], ',') !== FALSE){
						$Exp = explode(',', $CronJob['dow']);
						foreach($Exp as $ExpA=>$ExpB){
							if((int)$ExpB == (int)date('w', $CurrentTime)){
								break;
							}elseif($ExpA == (count($Exp) - 1)){
								continue 2;
							}
						}
					}else{
						continue;
					}
				}
				// Check if Month of the Year matches
				if((int)$CronJob['moy'] != (int)date('n', $CurrentTime) && $CronJob['moy'] != '*'){
					if(strpos($CronJob['moy'], ',') !== FALSE){
						$Exp = explode(',', $CronJob['moy']);
						foreach($Exp as $ExpA=>$ExpB){
							if((int)$ExpB == (int)date('n', $CurrentTime)){
								break;
							}elseif($ExpA == (count($Exp) - 1)){
								continue 2;
							}
						}
					}else{
						continue;
					}
				}
				// Check if Day of the Month matches
				if((int)$CronJob['dom'] != (int)date('j', $CurrentTime) && $CronJob['dom'] != '*'){
					if(strpos($CronJob['dom'], ',') !== FALSE){
						$Exp = explode(',', $CronJob['dom']);
						foreach($Exp as $ExpA=>$ExpB){
							if((int)$ExpB == (int)date('j', $CurrentTime)){
								break;
							}elseif($ExpA == (count($Exp) - 1)){
								continue 2;
							}
						}
					}else{
						continue;
					}
				}
				// Check if Hour matches
				if((int)$CronJob['hour'] != (int)date('G', $CurrentTime) && $CronJob['hour'] != '*'){
					if(strpos($CronJob['hour'], ',') !== FALSE){
						$Exp = explode(',', $CronJob['hour']);
						foreach($Exp as $ExpA=>$ExpB){
							if((int)$ExpB == (int)date('G', $CurrentTime)){
								break;
							}elseif($ExpA == (count($Exp) - 1)){
								continue 2;
							}
						}
					}else{
						continue;
					}
				}
				// Check for an "every X minutes" example
				if(strpos($CronJob['minute'], '/') !== FALSE){
					$GivenMinute = str_replace('*/', '', $CronJob['minute']);
					if((int)date('i', $CurrentTime) == 0){
						continue;
					}elseif(((int)date('i', $CurrentTime) % (int)$GivenMinute) != 0){
						continue;
					}
				}elseif((int)$CronJob['minute'] != (int)date('i', $CurrentTime) && $CronJob['minute'] != '*'){
					// Check if Minute matches
					if(strpos($CronJob['minute'], ',') !== FALSE){
						$Exp = explode(',', $CronJob['minute']);
						foreach($Exp as $ExpA=>$ExpB){
							if((int)$ExpB == (int)date('i', $CurrentTime)){
								break;
							}elseif($ExpA == (count($Exp) - 1)){
								continue 2;
							}
						}
					}else{
						continue;
					}
				}
				// Everything matches, add to list of jobs ran
				$Output[] = date('m/d/Y g:iA', $CurrentTime) . ': ' . implode(' ', $CronJob);
			}
			// Increment via Minutes
			$CurrentTime = ($CurrentTime + 60);
		}
		// Output scheduled array via JSON
		echo json_encode($Output);
	}
}
// Add cron jobs
VisualCron::AddCron('42 0 1 3,6,9,12 * <RunThisCommand>');
VisualCron::AddCron('3 22 * * 5 <RunThisCommand>');
VisualCron::AddCron('3 21 * * 5 <RunThisCommand>');
VisualCron::AddCron('3 1 * * * <RunThisCommand>');
VisualCron::AddCron('3 2 * * * <RunThisCommand>');
VisualCron::AddCron('*/13 * * * * <RunThisCommand>');
VisualCron::AddCron('*/7 * * * * <RunThisCommand>');

// View Output prediction
VisualCron::ViewCron();
?>
