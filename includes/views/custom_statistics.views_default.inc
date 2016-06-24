<?php
/**
 * @file
 * Contains default view for Custom statistics module.
 */

/**
 * Provides Statistics view which can be used as-is for displaying statistics.
 */
function custom_statistics_default_views() {
  $view = new view();
  $view->name = 'statistics';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'custom_statistics_db';
  $view->human_name = 'Statistics';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Statistics';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'custom statistics view tab';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid' => 'nid',
    'name' => 'name',
    'timestamp' => 'timestamp',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'timestamp' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Statistics: Nid */
  $handler->display->display_options['relationships']['nid']['id'] = 'nid';
  $handler->display->display_options['relationships']['nid']['table'] = 'custom_statistics_db';
  $handler->display->display_options['relationships']['nid']['field'] = 'nid';
  /* Relationship: Statistics: Uid */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'custom_statistics_db';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Statistics: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'custom_statistics_db';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  /* Field: COUNT(Statistics: Timestamp) */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'custom_statistics_db';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['group_type'] = 'count';
  $handler->display->display_options['fields']['timestamp']['label'] = 'Views';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Statistics: Timestamp */
  $handler->display->display_options['filters']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['filters']['timestamp']['table'] = 'custom_statistics_db';
  $handler->display->display_options['filters']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['filters']['timestamp']['operator'] = '>=';
  $handler->display->display_options['filters']['timestamp']['exposed'] = TRUE;
  $handler->display->display_options['filters']['timestamp']['expose']['operator_id'] = 'timestamp_op';
  $handler->display->display_options['filters']['timestamp']['expose']['label'] = 'From';
  $handler->display->display_options['filters']['timestamp']['expose']['description'] = 'Starting date in YYYY-MM-DD HH:MM:SS format';
  $handler->display->display_options['filters']['timestamp']['expose']['operator'] = 'timestamp_op';
  $handler->display->display_options['filters']['timestamp']['expose']['identifier'] = 'timestamp';
  $handler->display->display_options['filters']['timestamp']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['timestamp']['group_info']['label'] = 'Timestamp';
  $handler->display->display_options['filters']['timestamp']['group_info']['identifier'] = 'timestamp';
  $handler->display->display_options['filters']['timestamp']['group_info']['default_group'] = '1';
  $handler->display->display_options['filters']['timestamp']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'From',
      'operator' => '>=',
      'value' => array(
        'type' => 'date',
        'value' => '1',
        'min' => '',
        'max' => '',
      ),
    ),
    2 => array(
      'title' => 'To',
      'operator' => '<=',
      'value' => array(
        'type' => 'date',
        'value' => '2',
        'min' => '',
        'max' => '',
      ),
    ),
    3 => array(
      'title' => '',
      'operator' => '=',
      'value' => array(
        'type' => 'date',
        'value' => '',
        'min' => '',
        'max' => '',
      ),
    ),
  );
  /* Filter criterion: Statistics: Timestamp */
  $handler->display->display_options['filters']['timestamp_1']['id'] = 'timestamp_1';
  $handler->display->display_options['filters']['timestamp_1']['table'] = 'custom_statistics_db';
  $handler->display->display_options['filters']['timestamp_1']['field'] = 'timestamp';
  $handler->display->display_options['filters']['timestamp_1']['operator'] = '<=';
  $handler->display->display_options['filters']['timestamp_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['timestamp_1']['expose']['operator_id'] = 'timestamp_1_op';
  $handler->display->display_options['filters']['timestamp_1']['expose']['label'] = 'To';
  $handler->display->display_options['filters']['timestamp_1']['expose']['description'] = 'Ending date in YYYY-MM-DD HH:MM:SS format';
  $handler->display->display_options['filters']['timestamp_1']['expose']['operator'] = 'timestamp_1_op';
  $handler->display->display_options['filters']['timestamp_1']['expose']['identifier'] = 'timestamp_1';
  $handler->display->display_options['filters']['timestamp_1']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    3 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'node/%/statistics';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Custom statistics';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'user-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['statistics'] = array(
    t('Master'),
    t('Statistics'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Nid'),
    t('.'),
    t(','),
    t('Name'),
    t('Views'),
    t('All'),
    t('From'),
    t('Starting date in YYYY-MM-DD HH:MM:SS format'),
    t('Timestamp'),
    t('To'),
    t('Ending date in YYYY-MM-DD HH:MM:SS format'),
    t('Page'),
  );
  $views[$view->name] = $view;

  return $views;
}
