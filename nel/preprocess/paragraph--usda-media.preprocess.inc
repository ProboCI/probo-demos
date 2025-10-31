<?php

/**
 * Implements hook_preprocess_paragraph__usda_media().
 */
function nel_preprocess_paragraph__usda_media(&$variables) {
  $media = $variables['paragraph'];

  // Add the media class
  $variables['attributes']['class'][] = 'usda-media';

  // Set up zoomable media
  $zoom = $media->field_media_zoom->value;
  if ($zoom) {
    $variables['attributes']['class'][] = 'usda-media-zoom';
  }
  $variables['zoom'] = $zoom ? true : false;

  // Set style
  $styleClass = null;
  $style = $media->field_media_style->value;
  if ($style) {
    switch ($style) {
      case 'blue_frame':
        $styleClass = 'usda-media-blue-frame';
      break;
      case 'default':
      default:
        // no class
      break;
    }
  }
  if ($styleClass) {
    $variables['attributes']['class'][] = $styleClass;
  }


  // Add caption as data attribute
  $caption = $media->field_media_caption->value;
  $variables['attributes']['data-caption'] = is_string($caption) ? htmlspecialchars($caption) : '';
  // $variables['attributes']['data-caption'] = addcslashes($caption, '"');

}
