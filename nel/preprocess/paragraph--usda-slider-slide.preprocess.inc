<?php

/**
 * Implements hook_preprocess_paragraph__usda_slider_slide().
 */
function nel_preprocess_paragraph__usda_slider_slide(&$variables) {
  $panel = $variables['paragraph'];

  // Add the panel class
  $variables['attributes']['class'][] = 'usda-slider-slide';

  $variables['image_url'] = null;
  $imgField = $panel->field_media;
  if ($imgField) {
    // Image field found, let's get its URL
    $uri = $imgField->entity->get('field_media_image')->entity->uri->value;
    if ($uri) $variables['image_url'] = \Drupal::service('file_url_generator')->generateString($uri);
  }

}
