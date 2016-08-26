function octaveAnimate(fNameDelay)
  # Since octave does not have a way to animate graphs this is a somewhat
  # dirty why of creating animates graphs.
  # The graphs are appended to a PDF file and the the PDF file is turned 
  # into a gif file.
  #
  # Usage:
  # octaveAnimate('fileName')  # Init animation 
  #
  # for .......
  #     octaveAnimate()  # Add graph to PDF file
  # end
  # octaveAnimate(delay) # Delay is the time between graphs in the animation.
  #
  # See: eulerDemo.m
  #
  persistent fName;

  if (nargin == 0)
    print([fName '.pdf'], '-append')
  end

  if (nargin == 1)
    if (length(fNameDelay) > 1)
      fName = fNameDelay;
      # If file exists delete to prevent appending to old file
      system( ['rm ' fName '.pdf'] );
    end
    
    if (length(fNameDelay) == 1)
      im = imread ([fName '.pdf'], "Index", "all");
      imwrite (im, [fName '.gif'], "DelayTime", fNameDelay);
    end  
  end
end