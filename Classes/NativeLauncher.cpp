/*
 * NativeLauncher.cpp
 *
 *  Created on: 2015/02/21
 *      Author: yasutomo
 */


#include "NativeLauncher.h"


//レビューに誘導
void NativeLauncher::openReview(){

	Intent intent = new Intent(
	        Intent.ACTION_VIEW,
	        Uri.parse("https://play.google.com/store/apps/developer?id=https://play.google.com/store/apps/details?id=jp.sacrew.witchrace&amp;hl=ja&amp;hl=ja"));

	startActivity(intent);

}

void NativeLauncher::openTweetDialog(const char *$tweet){

}
