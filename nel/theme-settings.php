<?php

/**
 * Custom theme setting form elements for the USWDS theme.
 */

use \Drupal\Core\Link;
use \Drupal\Core\Url;

/**
 * Implements hook_form_system_theme_settings_alter().
 */
function nel_form_system_theme_settings_alter(&$form, \Drupal\Core\Form\FormStateInterface &$form_state, $form_id = NULL) {

  // Social links
  $form['social_links_fieldset'] = [
    '#type' => 'details',
    '#title' => t('Social links'),
    '#open' => TRUE,
    'usda_twitter' => [
      '#type' => 'textfield',
      '#title' => t('Twitter link'),
      '#default_value' => theme_get_setting('usda_twitter'),
    ],
    'usda_facebook' => [
      '#type' => 'textfield',
      '#title' => t('Facebook link'),
      '#default_value' => theme_get_setting('usda_facebook'),
    ],
    'usda_instagram' => [
      '#type' => 'textfield',
      '#title' => t('Instagram link'),
      '#default_value' => theme_get_setting('usda_instagram'),
    ],
    'usda_flickr' => [
      '#type' => 'textfield',
      '#title' => t('Flickr link'),
      '#default_value' => theme_get_setting('usda_flickr'),
    ],
    'usda_youtube' => [
      '#type' => 'textfield',
      '#title' => t('YouTube link'),
      '#default_value' => theme_get_setting('usda_youtube'),
    ],
    'usda_govdelivery' => [
      '#type' => 'textfield',
      '#title' => t('GovDelivery link'),
      '#default_value' => theme_get_setting('usda_govdelivery'),
    ],
    'usda_rss' => [
      '#type' => 'textfield',
      '#title' => t('RSS feed'),
      '#default_value' => theme_get_setting('usda_rss'),
    ],
  ];
}
