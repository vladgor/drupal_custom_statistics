<?php
/**
 * @file
 * File containing rendering informaton for module settings page.
 */

/**
 * Creates administrator interface for module settings.
 */
function custom_statistics_admin_settings() {

  $temp = node_type_get_types();
  // Extracts node type names from array.
  foreach ($temp as $type) {
    $node_types[$type->type] = $type->type;
  }

  // 'Node types to track' checkboxes.
  $form['custom_statistics_tracked_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Node types to track'),
    '#description' => t('Select node types that will be tracked by module.'),
    '#options' => $node_types,
    '#default_value' => variable_get('custom_statistics_tracked_node_types'),
  );

  $temp = user_roles();
  // Renames array keys into something more meaningful.
  foreach ($temp as $role) {
    $user_roles[$role] = $role;
  }

  // 'User roles to track' checkboxes.
  $form['custom_statistics_tracked_user_roles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('User roles to track'),
    '#description' => t('Select user roles that will be tracked by module.'),
    '#options' => $user_roles,
    '#default_value' => variable_get('custom_statistics_tracked_user_roles'),
  );

  // 'Reset statistics' title.
  $form['custom_statistics_reset_statistics_title'] = array(
    '#type' => 'item',
    '#title' => t('Enter your password to reset statistics:'),
  );
  // 'Reset statistics' container.
  $form['custom_statistics_reset_statistics_container'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('container-inline'),
    ),
    'custom_statistics_reset_statistics_password' => array(
      '#type' => 'password',
      '#maxlength' => 32,
      '#size' => 32,
    ),
    'custom_statistics_reset_statistics' => array(
      '#type' => 'submit',
      '#value' => t('Reset statistics'),
      '#submit' => array('custom_statistics_reset_statistics_submit'),
    ),
  );

  return system_settings_form($form);
}

/**
 * Checks entered password and if password is correct - erases statistics.
 */
function custom_statistics_reset_statistics_submit($form, &$form_state) {
  // Includes user_check_password() function.
  form_load_include($form_state, 'inc', 'content', 'includes/password');

  global $user;
  $container = $form['custom_statistics_reset_statistics_container'];
  $password = $container['custom_statistics_reset_statistics_password']['#value'];

  if (user_check_password($password, $user)) {
    custom_statistics_db_erase();
    drupal_set_message('Statistics were successfully erased.');
  }
  else {
    form_set_error('wrong_password', 'You have entered wrong password.');
  }
}
