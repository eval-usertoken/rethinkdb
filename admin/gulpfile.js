'use strict';
var gulp = require('gulp'),
    handlebars = require('gulp-handlebars'),
    lessc = require('gulp-less'),
    browserify = require('browserify'),
    source = require('vinyl-source-stream'),
    buffer = require('vinyl-buffer'),
    sourcemaps = require('gulp-sourcemaps'),
    coffee = require('gulp-coffee'),
    concat = require('gulp-concat'),
    gutil = require('gulp-util');

var BUILD_DIR = './build',
    STATIC_DIR = './static',
    COFFEE_DIR = STATIC_DIR+'/coffee',
    COFFEE_SRC = COFFEE_DIR+'/**/*.coffee',
    LESS_DIR = STATIC_DIR+'/less',
    TEMPLATE_DIR = STATIC_DIR+'/handlebars';


gulp.task('default', function() {
});

gulp.task('copy-files', function() {
  gulp.src(parameters.app_path+'/static/*')
    .pipe(gulp.dest(parameters.web_path+'/js/'));
});


gulp.task('coffee', function() {
  return gulp.src(COFFEE_SRC)
    .pipe(coffee({bare: true}).on('error', gutil.log))
    .pipe(concat, parameters.app_main_file)
    .pipe(gulp.dest(parameters.web_path+'/js'))
});