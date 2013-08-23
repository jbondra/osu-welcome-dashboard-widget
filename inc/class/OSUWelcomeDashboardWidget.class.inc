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
		
	}
	
	public function add_menus() {
		
	}
	
	public function options_page() {
		
	}
	
	public function welcome_dashboard_widget() {
		
	}
	
	public function add_dashboard_widgets() {
		
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
		
			wp_redirect( add_query_arg( $query_args, network_admin_url( 'settings.php?page=osu-welcome-dashboard-widget' ) ) );
			exit();
		}
	}
}
