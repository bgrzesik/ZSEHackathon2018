# Require any additional compass plugins here.

# Set this to the root of your project when deployed:
http_path = "/static"
css_dir = "css"
sass_dir = "scss"
images_dir = "img"
javascripts_dir = "js"



# You can select your preferred output style here (can be overridden via the command line):
# output_style = :expanded or :nested or :compact or :compressed
output_style = (environment == :development) ? :expanded : :compressed

# debugging comments that display the original location of your selectors.
line_comments = (environment == :development) ? true : false

if environment == :development
    sass_options = {:debug_info => true}
end