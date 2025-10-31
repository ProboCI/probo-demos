<?php

function nel_preprocess_node__systematic_review(&$variables) {

  $node = $variables['node'];

  // Get systematic review cover image
  $variables['cover_image'] = null;
  if (
    $node->hasField('field_systematic_review')
    && $node->field_systematic_review->entity
  ) {
    $review_entity = $node->field_systematic_review->entity;
    $imgEntity = $review_entity->get('field_cover_image')->entity;
    if ($imgEntity) {
      $uri = $imgEntity->get('field_media_image')->entity->uri->value;
      if ($uri) {
        $img = \Drupal::service('file_url_generator')->generateString($uri);
        $variables['cover_image'] = $img;
      }
    }
  }

}
