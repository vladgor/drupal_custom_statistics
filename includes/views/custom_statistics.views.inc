<?php
/**
 * @file
 * Views integration.
 */

/**
 * Explains how to display data in Views module.
 */
function custom_statistics_views_data() {
  $data[CUSTOM_STATISTICS_DB_TABLE_NAME] = array(
    'table' => array(
      'base' => array(
        'field' => 'nid',
        'title' => 'Statistics',
        'help' => 'Views integration for a Statistics table',
      ),
      'group' => 'Statistics',
      'join' => array(
        'node' => array(
          'left_field' => 'nid',
          'field' => 'nid',
        ),
        'users' => array(
          'left_field' => 'uid',
          'field' => 'uid',
        ),
      ),
    ),
    'nid' => array(
      'title' => 'Nid',
      'help' => 'The node ID',
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'relationship' => array(
        'base' => 'node',
        'base_field' => 'nid',
        'handler' => 'views_handler_relationship',
        'label' => t('Statistics'),
        'title' => t('Nid'),
        'help' => t('Contains rows from "node" table.'),
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'uid' => array(
      'title' => 'Uid',
      'help' => 'The user ID',
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'relationship' => array(
        'base' => 'users',
        'base_field' => 'uid',
        'handler' => 'views_handler_relationship',
        'label' => t('Statistics'),
        'title' => t('Uid'),
        'help' => t('Contains rows from "uid" table.'),
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'timestamp' => array(
      'title' => 'Timestamp',
      'help' => 'The view timestamp',
      'field' => array(
        'handler' => 'views_handler_field_date',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_date',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort_date',
      ),
    ),
  );
  return $data;
}
