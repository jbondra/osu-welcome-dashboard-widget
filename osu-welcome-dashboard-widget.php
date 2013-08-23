<?php
/**
 * osu-welcome-dashboard-widget.php
 * 	sets up OSU Welcome Dashboard Widget Plugin
 */

// constants
define( 'OSU_WELCOME_DASHBOARD_WIDGET_BASENAME', basename( dirname(__FILE__) ) );
define( 'OSU_WELCOME_DASHBOARD_WIDGET_DIR', dirname(__FILE__) );
define( 'OSU_WELCOME_DASHBOARD_WIDGET_URL', WPMU_PLUGIN_URL . '/' . OSU_WELCOME_DASHBOARD_WIDGET_BASENAME );

// activate plugin
if ( !class_exists('OSUWelcomeDashboardWidget') ) {
	require( 'inc/class/OSUWelcomeDashboardWidget.class.inc' );
}
$osu_welcome_dashboard_widget = new OSUWelcomeDashboardWidget();
