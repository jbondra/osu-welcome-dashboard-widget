<?php
/**
 * OSUWelcomeDashboardWidget.class.inc
 * 	Defines the OSUWelcomeDashboardWidget class 
 */

class OSUWelcomeDashboardWidget {
	public function OSUWelcomeDashboardWidget() {
		// actions	
		if ( is_admin() ) {
			add_action( 'admin_init', array( $this, 'admin_process_post' ) );
			add_action( 'network_admin_menu', array( $this, 'add_menus' ) );
			add_action( 'wp_dashboard_setup', array( $this, 'add_dashboard_widgets' ) );
		}
		add_action( 'muplugins_loaded', array( $this, 'create_options' ) );
		
	}
	
	public function create_options() {
		// create options if necessary
		$options = get_site_option( 'osu_welcome_dashboard_widget_options' );
		
		if( $options === false ) {
			// options do not yet exist, create options
			
			$options = array(
				'widget_content' => '',
			);
			
			add_site_option( 'osu_welcome_dashboard_widget_options', $options );
		}
	}
	
	public function add_menus() {
		add_submenu_page( 'settings.php', 'OSU Dashboard Welcome Widget', 'OSU Welcome Widget', 'manage_network_options', 'osu-dashboard-welcome-widget', array( $this, 'options_page') );
	}
	
	public function options_page() {
		// check for appropriate access
		if ( ! current_user_can( 'manage_network_options' ) )
			wp_die( __( 'You do not have permission to access this page.' ) );
		
		$options = get_site_option( 'osu_welcome_dashboard_widget_options' );
		$widget_content = wpautop( wp_kses_stripslashes( $options['widget_content'] ) );
		
		include( OSU_WELCOME_DASHBOARD_WIDGET_DIR . '/inc/view/options-page.view.inc' );
	}
	
	public function add_dashboard_widgets() {
		wp_add_dashboard_widget( 'osu_welcome_dashboard_widget', 'Welcome to U.OSU', array( $this, 'welcome_dashboard_widget' ) );
		
		// Globalize the metaboxes array, this holds all the widgets for wp-admin
		
		// move widget to top (http://codex.wordpress.org/Dashboard_Widgets_API#Advanced:_Forcing_your_widget_to_the_top)
		global $wp_meta_boxes;
		
		// Get the regular dashboard widgets array 
		// (which has our new widget already but at the end)
	
		$normal_dashboard = $wp_meta_boxes['dashboard']['normal']['core'];
		
		// Backup and delete our new dashboard widget from the end of the array
	
		$osu_welcome_dashboard_widget_backup = array('osu_welcome_dashboard_widget' => $normal_dashboard['osu_welcome_dashboard_widget']);
		unset($normal_dashboard['osu_welcome_dashboard_widget']);
	
		// Merge the two arrays together so our widget is at the beginning
	
		$sorted_dashboard = array_merge($osu_welcome_dashboard_widget_backup, $normal_dashboard);
	
		// Save the sorted array back into the original metaboxes 
	
		$wp_meta_boxes['dashboard']['normal']['core'] = $sorted_dashboard;
	}
	
	public function welcome_dashboard_widget() {
		// get agreement text
		$options = get_site_option( 'osu_welcome_dashboard_widget_options' );
		$widget_content = wpautop( wp_kses_stripslashes( $options['widget_content'] ) );
		
		// will need to drive any headings down a notch... widget headings are h3
		$widget_content = OSUWelcomeDashboardWidget::move_headings_down( $widget_content, 4 );
		
		echo $widget_content;
	}
	
	public function admin_process_post() {
		if ( isset( $_POST['osu_welcome_dashboard_widget_options'] ) && current_user_can( 'manage_network_options' ) ) {
			check_admin_referer( 'osu_welcome_dashboard_widget_options' );
			
			$new_options = array();
			$current_options = get_site_option( 'osu_welcome_dashboard_widget_options' );
		
			if ( isset( $_POST['osu_welcome_dashboard_widget_options']['widget_content'] ) ) {
				$widget_content = wp_kses_post( $_POST['osu_welcome_dashboard_widget_options']['widget_content'] );
				
				$new_options['widget_content'] = $widget_content;
			}
			
			$options = array_merge( $current_options, $new_options );
			
			update_site_option( 'osu_welcome_dashboard_widget_options', $options );
			
			$query_args = array(
				'updated' => 'true',
			);
		
			wp_redirect( add_query_arg( $query_args, network_admin_url( 'settings.php?page=osu-dashboard-welcome-widget' ) ) );
			exit();
		}
	}
	
	/**
	 * move_headings_down
	 * 	a convenience function to display terms of service html headings in context (for valid markup)
	 */
	private function move_headings_down( $html_str, $highest_level = 2 ) {
		if ( $highest_level > 6 ) {
			$highest_level = 6;
		}
		
		for( $i = 1; $i <= $highest_level - 1; $i++ ) {
			for( $j = 5; $j >= 1; $j-- )
			{
				$new_level = $j + 1;
				$html_str = str_replace( "<h{$j}>", "<h{$new_level}>", $html_str );
				$html_str = str_replace( "</h{$j}>", "</h{$new_level}>", $html_str );
			}
		}

		return $html_str;
	}
}
