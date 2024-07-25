#include <SFML/Graphics.hpp>
#include <random>
#include "CCarousel.h"

class ShakeSpinningCard
{
private:
    CCarousel::cardHandler* m_spinningCard;
    float m_shakeIntensity;
    float m_shakeDuration;
    float m_shakeElapsedTime;
    float m_originalAngle;
    float m_originalVerticalAngle;
    float m_targetAngle;
    int m_currentFrame;
    int m_framesPerTarget;
    bool vert;
    float* timer;


public:
    ShakeSpinningCard()
    {
        m_spinningCard = NULL;
    }

    ShakeSpinningCard(CCarousel::cardHandler* spinningCard,float* timer_): m_spinningCard(spinningCard), m_shakeIntensity(0.f), m_shakeDuration(0.f), m_shakeElapsedTime(0.f),
        m_originalAngle(0.f), m_originalVerticalAngle(0.f), m_targetAngle(0.f), m_currentFrame(0), m_framesPerTarget(3), vert(false), timer(timer_)
    {
}

    void spin(float angleInDegrees)
    {
        m_originalAngle = angleInDegrees;
        m_spinningCard->spin(angleInDegrees);
    }

    void spinVertically(float angleInDegrees)
    {
        m_originalVerticalAngle = angleInDegrees;
        m_spinningCard->spinVertically(angleInDegrees);
    }

    void shake(float intensity, float duration)
    {
        m_shakeIntensity = intensity;
        m_shakeDuration = duration;
        m_shakeElapsedTime = *timer;
        m_targetAngle = 0.f;
        m_currentFrame = 0;
    }

    bool update(float deltaTime)
    {
        if (*timer-m_shakeElapsedTime < m_shakeDuration)
        {
            if (m_currentFrame == 0)
            {
                std::default_random_engine generator;
                std::uniform_real_distribution<float> distribution(-m_shakeIntensity, m_shakeIntensity);

                m_targetAngle = distribution(generator);
                m_targetAngle = (m_targetAngle < 0.f) ? 360 + m_targetAngle : m_targetAngle;
            }

            float progress = (m_currentFrame + 1) / static_cast<float>(m_framesPerTarget);
            float spinAngle = m_targetAngle * progress;

            if (vert)
            {
                m_spinningCard->spin(spinAngle);
            }
            else
            {
                m_spinningCard->spinVertically(spinAngle);
            }

            vert = !vert;
            m_currentFrame = (m_currentFrame + 1) % m_framesPerTarget;

            return false; // Shake is not done yet
        }
        else
        {
            // Reset to original angles when shaking is done
            m_spinningCard->spin(m_originalAngle);
            m_spinningCard->spinVertically(m_originalVerticalAngle);

            std::cout << "end shaking" << std::endl;
            return true; // Shake is done
        }
    }

    void draw(sf::RenderTarget& target) const
    {
        m_spinningCard->draw(target);
    }

};