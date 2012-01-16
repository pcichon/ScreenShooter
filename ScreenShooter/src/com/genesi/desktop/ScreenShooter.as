/**
 * ScreenShooter // Adobe AIR3.*
 * 
 * Source: https://github.com/pcichon/ScreenShooter
 * 
 * @author		Pawel Cichon
 * @version		0.1
 */

package com.genesi.desktop
{
	import flash.display.BitmapData;
	import flash.external.ExtensionContext;
	import flash.utils.ByteArray;
	
	public class ScreenShooter
	{
		private var context:ExtensionContext;
		
		public function ScreenShooter()
		{
			context = ExtensionContext.createExtensionContext('com.genesi.desktop.ScreenShooter', '');
		}
						
		public function getScreenShot():ByteArray
		{
			var bytes:ByteArray = new ByteArray();
			context.call('getScreenShot', bytes);
			return bytes;
		}
					
	}
}