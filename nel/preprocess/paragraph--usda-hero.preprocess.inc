<?php

/**
 * Implements hook_preprocess_paragraph__usda_hero().
 */
function nel_preprocess_paragraph__usda_hero(&$variables) {

  // Set the inline CSS for the image
  if (!$variables['paragraph']->field_media->isEmpty()) {

    // Make sure we have a unique ID, in case of multiple Heroes
    $identifier = 'usda-hero-' . $variables['paragraph']->field_media->entity->id();
    $variables['attributes']['class'][] = $identifier;

    // This doesn't work when there are multiple hero paragraphs on the same page.
    // The second paragraph never gets the following CSS added to the <head> tag.
    //
    // Inline the CSS background image
    // $uri = $variables['paragraph']->field_media->entity->get('field_media_image')->entity->uri->value;
    // $img = \Drupal::service('file_url_generator')->generateString($uri);
    // $css = ".$identifier.paragraph--type--usda-hero.usa-hero { background-image:url($img); }";
    // $variables['#attached']['html_head'][] = [
    //   [
    //     '#tag' => 'style',
    //     '#value' => $css,
    //   ],
    //   'usda-hero'
    // ];

    // Get image
    $variables['image_url'] = null;
    $imgField = $variables['paragraph']->field_media;
    if ($imgField) {
      // Image field found, let's get its URL
      $uri = $imgField->entity->get('field_media_image')->entity->uri->value;
      if ($uri) $variables['image_url'] = \Drupal::service('file_url_generator')->generateString($uri);
    }


  }
}
